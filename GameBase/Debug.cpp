#include "stdafx.h"
#include "Debug.h"
#include "Input.h"
#include "Player.h"
#include "EnemyBase.h"
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
    clsDx();

    // F1‚ª‰Ÿ‚³‚ê‚Ä‚¢‚È‚©‚Á‚½‚ç‘ŠúƒŠƒ^[ƒ“
	if (!isDebugMode) return;

	for (auto obj : owner)
	{
		if (obj->GetIsCollisionEnabled())
		{
			DrawCapsule(obj);

		}

        if (obj->GetName() == "Player")
        {
            DrawCylinder(obj->GetPosition(), 30, 10, 32, GetColor(255, 0, 0));
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
        DrawCylinder(enemy->GetPosition(), 60, 10, 32, GetColor(255, 255, 0));
        DrawCylinder(enemy->GetPosition(), 30, 10, 32, GetColor(255, 0, 0));
    }

    printfDx("LeftStickX : %.0f \n", Input::GetInput().GetLeftStickX());
    printfDx("LeftStickY : %.0f \n", Input::GetInput().GetLeftStickY());
    printfDx("LeftStickPower : %.0f \n", Input::GetInput().GetLeftStickPower());


}

// ƒJƒvƒZƒ‹‚Ì•`‰æ
void Debug::DrawCapsule(const std::shared_ptr<IGameObject>& obj)
{
	DrawCapsule3D(obj->GetTopPos(), obj->GetBottomPos()
		, obj->GetHitRadius(), 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
}

// ‰~’Œ‚Ì•`‰æ
void Debug::DrawCylinder(VECTOR pos, float radius, float height, float division, unsigned int color)
{
    float yTop = pos.y + height / 2.0f;
    float yBottom = pos.y - height / 2.0f;

    // ’¸“_‚ğŒvZ‚µ‚Äü‚ğ•`‰æ
    for (int i = 0; i < division; i++)
    {
        float angle1 = 2.0f * DX_PI_F * i / division;
        float angle2 = 2.0f * DX_PI_F * (i + 1) / division;

        VECTOR top1 = VGet(pos.x + cosf(angle1) * radius, yTop, pos.z + sinf(angle1) * radius);
        VECTOR top2 = VGet(pos.x + cosf(angle2) * radius, yTop, pos.z + sinf(angle2) * radius);
        VECTOR bottom1 = VGet(pos.x + cosf(angle1) * radius, yBottom, pos.z + sinf(angle1) * radius);
        VECTOR bottom2 = VGet(pos.x + cosf(angle2) * radius, yBottom, pos.z + sinf(angle2) * radius);

        // ‘¤–Ê‚Ìü
        DrawLine3D(top1, bottom1, color);
        DrawLine3D(top2, bottom2, color);

        // ã–Ê‚Ìü
        DrawLine3D(top1, top2, color);

        // ‰º–Ê‚Ìü
        DrawLine3D(bottom1, bottom2, color);
    }
}