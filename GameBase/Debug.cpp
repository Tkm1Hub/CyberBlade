#include "stdafx.h"
#include "Debug.h"
#include "Input.h"
#include "Player.h"
#include "EnemyBase.h"
#include "EnemySmall.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "EnemyBig.h"
#include "EffectManager.h"

void Debug::Update()
{
	bool nowF1 = (CheckHitKey(KEY_INPUT_F1) != 0);
	if (nowF1 && !prevF1)
	{
		isDebugMode = !isDebugMode;
	}

    if (isDebugMode)
    {
        if (CheckHitKey(KEY_INPUT_UP))
        {
            float timeScale = TimeManager::GetInstance().GetTimeScale();
            timeScale += 0.01f;
            TimeManager::GetInstance().SetTimeScale(timeScale);
        }
        else if (CheckHitKey(KEY_INPUT_DOWN))
        {
            float timeScale = TimeManager::GetInstance().GetTimeScale();
            timeScale -= 0.01f;
            TimeManager::GetInstance().SetTimeScale(timeScale);
        }
    }

	prevF1 = nowF1;
}
void Debug::Draw()
{
    clsDx();

    // F1が押されていなかったら早期リターン
	if (!isDebugMode) return;

	for (auto obj : owner)
	{
		if (obj->GetIsCollisionEnabled())
		{
			DrawCapsule(obj);

		}

        if (obj->GetName() == "Player")
        {
            auto player = std::dynamic_pointer_cast<Player>(obj);
            DrawCylinder(player->GetPosition(), 30, 10, 32, GetColor(255, 0, 0));

            // 回避中はジャスト回避用の当たり判定を描画
            if (player->GetIsDodge())
            {
                DrawCapsule3D(player->GetTopPos(), player->GetBottomPos()
                    , player->GetDodgeHitRadius(), 8, GetColor(0, 0, 180), GetColor(255, 255, 255), FALSE);
            }

            printfDx("isInvncible : %s \n", player->GetIsInvincible() ? "true" : "false");
        }

        if (obj->GetName() == "CheckPoint")
        {
            DrawCylinder(obj->GetPosition(), obj->GetHitRadius(),
                obj->GetHitHeight(), 32, GetColor(50, 50, 255));
        }
	}

    for (auto enemy : m_enemies)
    {
        if (!enemy->GetIsDead())
        {
            // 当たり判定カプセル
            DrawCapsule(enemy);
            // 攻撃（手）の当たり判定
            DrawSphere3D(enemy->GetHandPos(), enemy->GetHandHitRadius(), 16, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
            
            if (enemy->GetName() == "EnemyBoss")
            {
                auto enemyBoss = std::dynamic_pointer_cast<EnemyBig>(enemy);

                DrawCylinder(enemyBoss->GetPosition(), enemyBoss->GetWarningRadius(), 10.0f, 64, GetColor(255, 30, 30));
                DrawCylinder(enemyBoss->GetPosition(), enemyBoss->GetAttack1TriggerRadius(), 10.0f, 64, GetColor(180, 180, 0));
                
                if (CheckHitKey(KEY_INPUT_F3))
                {
                    EffectManager::GetInstance().PlayEffect("Boss_Roar", enemyBoss->GetPosition());
                }
                if (CheckHitKey(KEY_INPUT_F4))
                {
                    EffectManager::GetInstance().PlayEffect("Attack_Warning", enemyBoss->GetPosition());
                }
            }
        }


    }

    printfDx("LeftStickX : %.0f \n", Input::GetInput().GetLeftStickX());
    printfDx("LeftStickY : %.0f \n", Input::GetInput().GetLeftStickY());
    printfDx("LeftStickPower : %.0f \n", Input::GetInput().GetLeftStickPower());
    printfDx("TimeScale : %.2f \n", TimeManager::GetInstance().GetTimeScale());

}

// カプセルの描画
void Debug::DrawCapsule(const std::shared_ptr<IGameObject>& obj)
{
	DrawCapsule3D(obj->GetTopPos(), obj->GetBottomPos()
		, obj->GetHitRadius(), 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
}

// 円柱の描画
void Debug::DrawCylinder(VECTOR pos, float radius, float height, float division, unsigned int color)
{
    float yTop = pos.y + height / 2.0f;
    float yBottom = pos.y - height / 2.0f;

    // 頂点を計算して線を描画
    for (int i = 0; i < division; i++)
    {
        float angle1 = 2.0f * DX_PI_F * i / division;
        float angle2 = 2.0f * DX_PI_F * (i + 1) / division;

        VECTOR top1 = VGet(pos.x + cosf(angle1) * radius, yTop, pos.z + sinf(angle1) * radius);
        VECTOR top2 = VGet(pos.x + cosf(angle2) * radius, yTop, pos.z + sinf(angle2) * radius);
        VECTOR bottom1 = VGet(pos.x + cosf(angle1) * radius, yBottom, pos.z + sinf(angle1) * radius);
        VECTOR bottom2 = VGet(pos.x + cosf(angle2) * radius, yBottom, pos.z + sinf(angle2) * radius);

        // 側面の線
        DrawLine3D(top1, bottom1, color);
        DrawLine3D(top2, bottom2, color);

        // 上面の線
        DrawLine3D(top1, top2, color);

        // 下面の線
        DrawLine3D(bottom1, bottom2, color);
    }
}