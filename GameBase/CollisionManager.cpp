#include "stdafx.h"
#include "CollisionManager.h"
#include "StageCollision.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EnemySmall.h"
#include "Sword.h"
#include "Stage.h"
#include "Player_DodgeJustState.h"
#include "CameraManager.h"
#include "EffectManager.h"

void CollisionManager::Init()
{
	stageCollision = std::make_shared<StageCollision>();

	for (auto obj : objects)
	{
		// ステージモデルのハンドルを渡す
		if (obj->GetName() == "Stage")
		{
            m_pStage = std::dynamic_pointer_cast<Stage>(obj);

            int modelHandle = m_pStage->GetCollisionModelHandle();
			stageCollision->SetStageCollision(modelHandle);
		}
		// プレイヤーのポインタを渡す
		if (obj->GetName() == "Player")
		{
			m_pPlayer = std::dynamic_pointer_cast<Player>(obj);
		}
		// 刀のポインタを渡す
		if (obj->GetName() == "Sword")
		{
			m_pSword = std::dynamic_pointer_cast<Sword>(obj);
		}
	}
}

void CollisionManager::Update()
{
    // プレイヤーが攻撃中の場合、敵と刀の当たり判定を行う
    if (m_pPlayer->GetIsAttack())
    {
        CheckSwordEnemyCollision();
    }

    CheckEnemyAttackPlayerCollision();

    // オブジェクト同士の押し戻し
    for (size_t i = 0; i < m_pEnemies.size(); i++)
    {
        for (size_t j = i + 1; j < m_pEnemies.size(); j++)
        {
            if (!m_pEnemies[i]->GetIsDead())
            {
                ResolveCapsuleCollision(m_pEnemies[i], m_pEnemies[j]);
            }
        }

        // プレイヤーと敵の衝突
        if (m_pPlayer)
        {
            if (!m_pEnemies[i]->GetIsDead())
            {
                ResolveCapsuleCollision(m_pPlayer, m_pEnemies[i]);
            }
        }
    }

    // ステージとの衝突
	for (auto obj : objects)
	{
		if (obj->GetIsStageCollisionEnabled())
		{
			VECTOR nextPos = stageCollision->CheckCollision(*obj, obj->GetNextPosition());
			obj->SetNextPosition(nextPos);
		}
	}

    for (auto enemy : m_pEnemies)
    {
        VECTOR nextPos = stageCollision->CheckCollision(*enemy, enemy->GetNextPosition());
        enemy->SetNextPosition(nextPos);
    }
}

// 敵と刀の当たり判定
void CollisionManager::CheckSwordEnemyCollision()
{
    for (auto enemy : m_pEnemies)
    {
        if (CheckCapsuleCollision(enemy, m_pSword))
        {
            if (!enemy->GetDamageFlag() && m_pPlayer->GetIsAttackEnabled())
            {
                // カメラ揺れ
                CameraManager::GetCameraManager().GetMainCamera()->StartShake(1.3f,0.0f, 15.0f);

                // 現在のアニメ番号によってエフェクトを再生
                int currentAnimNum = m_pPlayer->animation.GetCurrentAnimNum();
                switch (currentAnimNum)
                {
                case (static_cast<int>(PlayerAnimState::AttackJump1)):
                {
                    EffectManager::GetInstance().PlayEffect("Slash1", m_pSword->GetTopPos());
                    EffectManager::GetInstance().SetRotation("Slash1", MV1GetRotationXYZ(m_pPlayer->GetModelHandle()));
                    break;
                }
                case (static_cast<int>(PlayerAnimState::AttackJump2)):
                {
                    EffectManager::GetInstance().PlayEffect("Slash2", m_pSword->GetTopPos());
                    EffectManager::GetInstance().SetRotation("Slash2", MV1GetRotationXYZ(m_pPlayer->GetModelHandle()));
                    break;
                }
                case (static_cast<int>(PlayerAnimState::Attack3)):
                {
                    EffectManager::GetInstance().PlayEffect("Slash3", m_pSword->GetTopPos());
                    EffectManager::GetInstance().SetRotation("Slash3", MV1GetRotationXYZ(m_pPlayer->GetModelHandle()));
                    break;
                }
                default:
                    return;
                }

                enemy->SetDamageFlag(true);
                enemy->ApplyDamage(20);
                VECTOR knockBackDirection = CulcKnockBackDirection(m_pPlayer,enemy);
                enemy->SetKnockBackDir(knockBackDirection);

                // このモーションでの攻撃を無効化
                m_pPlayer->SetIsAttackEnabled(false);
            }
        }
    }
}

// 敵の攻撃とプレイヤーの当たり判定
void CollisionManager::CheckEnemyAttackPlayerCollision()
{
    if (!m_pPlayer->GetDamageFlag())
    {
        for (auto enemy : m_pEnemies)
        {
            if (enemy->GetIsAttack())
            {
                if (m_pPlayer->GetIsDodge())
                {
                    if (m_pPlayer->GetIsDodgeJust())return;

                    if (CheckCapsuleSphereCollision(m_pPlayer->GetTopPos(), m_pPlayer->GetBottomPos(), m_pPlayer->GetDodgeHitRadius(), enemy->GetAttackCollisionPos(), enemy->GetAttackCollisionRadius()))
                    {
                        // ジャスト回避
                        auto spDodgeJustState = std::make_shared<Player_DodgeJustState>();
                        m_pPlayer->ChangeState(spDodgeJustState);
                        return;
                    }
                }
                else
                {
                    if (!m_pPlayer->GetIsInvincible())
                    {
                        if (CheckCapsuleSphereCollision(m_pPlayer->GetTopPos(), m_pPlayer->GetBottomPos(), m_pPlayer->GetHitRadius(), enemy->GetAttackCollisionPos(), enemy->GetAttackCollisionRadius()))
                        {
                            // ダメージ
                            m_pPlayer->SetDamageFlag(true);
                            m_pPlayer->ApplyDamage(20);
                            VECTOR knockBackDirection = CulcKnockBackDirection(enemy, m_pPlayer);
                            m_pPlayer->SetKnockBackDir(knockBackDirection);
                            m_pPlayer->SetDamageSourcePos(enemy->GetPosition());
                            // カメラ揺れ
                            CameraManager::GetCameraManager().GetMainCamera()->StartShake(1.5f, 1.5f, 25.0f);
                        }
                    }
                }
            }
        }
    }
}


// カプセル同士の当たり判定
bool CollisionManager::CheckCapsuleCollision(const std::shared_ptr<IGameObject> objA, const std::shared_ptr<IGameObject> objB)
{
	float RadiusA = objA->GetHitRadius();    // 半径

	float RadiusB = objB->GetHitRadius();    // 半径
    
    // カプセルの上下の座標を取得
    VECTOR TopA = objA->GetTopPos();
    VECTOR BottomA = objA->GetBottomPos();

    VECTOR TopB = objB->GetTopPos();
    VECTOR BottomB = objB->GetBottomPos();

	// カプセル間の最近接距離を計算（線分同士）
	float distance = DistanceSegmentToSegment(BottomA, TopA, BottomB, TopB);

	return distance < (RadiusA + RadiusB);		// カプセル同士の衝突判定
}

// カプセル同士の最短距離を求める
float CollisionManager::DistanceSegmentToSegment(VECTOR p1, VECTOR q1, VECTOR p2, VECTOR q2)
{
    VECTOR d1 = VSub(q1, p1);  // 線分1
    VECTOR d2 = VSub(q2, p2);  // 線分2
    VECTOR r = VSub(p1, p2);

    float a = VDot(d1, d1);  // 長さの2乗
    float e = VDot(d2, d2);
    float f = VDot(d2, r);

    float s, t;

    if (a <= 0.0001f && e <= 0.0001f)
    {
        return VSize(r); // 両方とも点
    }

    if (a <= 0.0001f)
    {
        s = 0.0f;
        t = f / e;
        t = (t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t));
    }
    else
    {
        float c = VDot(d1, r);
        if (e <= 0.0001f)
        {
            t = 0.0f;
            s = -c / a;
            s = (s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s));
        }
        else
        {
            float b = VDot(d1, d2);
            float denom = a * e - b * b;

            if (denom != 0.0f)
            {
                s = (b * f - c * e) / denom;
                s = (s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s));
            }
            else
            {
                s = 0.0f;
            }

            t = (b * s + f) / e;

            if (t < 0.0f)
            {
                t = 0.0f;
                s = (-c) / a;
                s = (s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s));
            }
            else if (t > 1.0f)
            {
                t = 1.0f;
                s = (b - c) / a;
                s = (s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s));
            }
        }
    }

    VECTOR c1 = VAdd(p1, VScale(d1, s));
    VECTOR c2 = VAdd(p2, VScale(d2, t));

    return VSize(VSub(c1, c2));
}

VECTOR CollisionManager::CulcKnockBackDirection(const std::shared_ptr<IGameObject>& attackObj, const std::shared_ptr<IGameObject>& damageObj)
{
    VECTOR attackerPos = attackObj->GetPosition();
    VECTOR damageObjPos = damageObj->GetPosition();

    VECTOR knockBackDirection = VSub(damageObjPos, attackerPos);
    knockBackDirection.y = 0.0f;
    knockBackDirection = VNorm(knockBackDirection);
    
    return knockBackDirection;
}

// カプセル同士の衝突をチェックして押し戻す
bool CollisionManager::ResolveCapsuleCollision(std::shared_ptr<IGameObject> objA, std::shared_ptr<IGameObject> objB)
{
    float radiusA = objA->GetHitRadius();
    float radiusB = objB->GetHitRadius();

    VECTOR topA = objA->GetTopPos();
    VECTOR bottomA = objA->GetBottomPos();

    VECTOR topB = objB->GetTopPos();
    VECTOR bottomB = objB->GetBottomPos();

    // --- カプセル B の軸に対する、カプセル A の最近接点 ---
    VECTOR closestA = ClosestPointOnSegment(bottomA, topA, bottomB);  // A軸上のB下端に最も近い点
    VECTOR closestB = ClosestPointOnSegment(bottomB, topB, bottomA);  // B軸上のA下端に最も近い点

    // A軸の最近接点 ＝ Bカプセルの最近接点
    // B軸の最近接点 ＝ Aカプセルの最近接点
    // → ２つの最も近い点同士で判定すればOK
    VECTOR diff = VSub(closestB, closestA);
    float dist = VSize(diff);
    float minDist = radiusA + radiusB;

    if (dist < minDist && dist > 0.0001f)
    {
        float penetration = minDist - dist;

        VECTOR pushDir = VNorm(diff);

        // 半分ずつ押し戻し
        VECTOR pushA = VScale(pushDir, -penetration * 0.5f);
        VECTOR pushB = VScale(pushDir, penetration * 0.5f);

        objA->SetNextPosition(VAdd(objA->GetNextPosition(), pushA));
       // objB->SetNextPosition(VAdd(objB->GetNextPosition(), pushB));

        return true;
    }

    return false;
}

// カプセルと球の当たり判定
bool CollisionManager::CheckCapsuleSphereCollision(const VECTOR&capTop,const VECTOR& capBottom,const float capRadius, const VECTOR& spherePos, float sphereRadius)
{
    VECTOR segment = VSub(capTop, capBottom);

    VECTOR toCenter = VSub(spherePos, capBottom);

    // 線分上のどの位置が最近接点になるか（0～1）
    float t = VDot(toCenter, segment) / VDot(segment, segment);

    // t を 0～1 にクランプ（はみ出し防止）
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    // 最近接点（カプセル軸上で球に一番近い点）
    VECTOR nearest = VAdd(capBottom, VScale(segment, t));

    // 最近接点と球の中心の距離
    float dist = VSize(VSub(nearest, spherePos));

    // 半径の合計
    float hitDist = capRadius + sphereRadius;

    return dist < hitDist;
}

// 点p に対して、線分 ab 上の最近接点を求める
VECTOR CollisionManager::ClosestPointOnSegment(const VECTOR& a, const VECTOR& b, const VECTOR& p)
{
    VECTOR ab = VSub(b, a);
    VECTOR ap = VSub(p, a);

    float abLenSq = VDot(ab, ab);
    if (abLenSq <= 0.00001f) return a; // 長さ0対策

    float t = VDot(ap, ab) / abLenSq;

    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    return VAdd(a, VScale(ab, t));
}