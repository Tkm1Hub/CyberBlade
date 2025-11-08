#include "stdafx.h"
#include "CollisionManager.h"
#include "StageCollision.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EnemySmall.h"
#include "Sword.h"
#include "Stage.h"


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
            if (!enemy->GetDamageFlag())
            {
                enemy->SetDamageFlag(true);
                enemy->ApplyDamage(20);
                VECTOR knockBackDirection = CulcKnockBackDirection(enemy);
                enemy->SetKnockBackDir(knockBackDirection);
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

VECTOR CollisionManager::CulcKnockBackDirection(const std::shared_ptr<EnemyBase>& enemy)
{
    VECTOR playerPos = m_pPlayer->GetPosition();
    VECTOR enemyPos = enemy->GetPosition();

    VECTOR directionEnemyToPlayer = VSub(playerPos, enemyPos);
    directionEnemyToPlayer.y = 0.0f;
    directionEnemyToPlayer = VNorm(directionEnemyToPlayer);
    
    VECTOR knockBackDirection = VScale(directionEnemyToPlayer, -1.0f);
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

    // 各カプセルの中心を求める
    VECTOR centerA = VScale(VAdd(topA, bottomA), 0.5f);
    VECTOR centerB = VScale(VAdd(topB, bottomB), 0.5f);

    // 2つの中心間のベクトル
    VECTOR diff = VSub(centerB, centerA);
    float dist = VSize(diff);
    float minDist = radiusA + radiusB;

    if (dist < minDist && dist > 0.0001f)
    {
        // 重なり量
        float penetration = minDist - dist;

        // 正規化
        VECTOR pushDir = VNorm(diff);

        // 双方を半分ずつ押し戻す（バランス型）
        VECTOR pushA = VScale(pushDir, -penetration * 0.5f);
        VECTOR pushB = VScale(pushDir, penetration * 0.5f);

        VECTOR newPosA = VAdd(objA->GetNextPosition(), pushA);
        VECTOR newPosB = VAdd(objB->GetNextPosition(), pushB);

        objA->SetNextPosition(newPosA);
        objB->SetNextPosition(newPosB);

        return true;
    }

    return false;
}