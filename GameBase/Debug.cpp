#include "stdafx.h"
#include "Debug.h"
#include "Input.h"
#include "Player.h"
#include "EnemySmall.h"
#include "ObjectManager.h"

void Debug::Update()
{
	bool nowF1 = (CheckHitKey(KEY_INPUT_F1) != 0);
	if (nowF1 && !prevF1)
	{
		isDebugMode = !isDebugMode;
	}

	prevF1 = nowF1;
}
void Debug::Draw()
{
	// F1が押されていなかったら早期リターン
	if (!isDebugMode) return;

	for (auto obj : owner)
	{
		if (obj->GetIsCollisionEnabled())
		{
			DrawCapsule(obj);

		}

        if (obj->GetName() == "CheckPoint")
        {
            DrawCylinder(obj->GetPosition(), obj->GetHitRadius(),
                obj->GetHitHeight(), 32, GetColor(50, 50, 255));
        }
	}

    for (auto enemy : m_enemies)
    {
        DrawCapsule(enemy);
    }
}


void Debug::DrawCapsule(const std::shared_ptr<IGameObject>& obj)
{
	DrawCapsule3D(obj->GetCapsuleAPos(), obj->GetCapsuleBPos()
		, obj->GetHitRadius(), 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
}

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