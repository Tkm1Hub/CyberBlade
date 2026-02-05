#include "stdafx.h"
#include "Marker.h"
#include "EnemyBase.h"
#include "EnemyManager.h"
#include "Player.h"

void Marker::Init()
{
	m_isActive = true;
}

void Marker::Update()
{
	if (auto p = m_pPlayer.lock())
	{
		VECTOR playerPos = p->GetPosition();
		VECTOR targetPos;

		if (p->GetIsLockOn())
		{
			// ロックオン状態ならターゲットの座標を指定
			auto target = p->GetLockOnTarget();
			if (!target)
			{
				m_isActive = false;
				return;
			}
			targetPos = target->GetLockOnPos();
		}
		else
		{
			// フリーカメラなら最短距離の敵の座標を指定
			auto target = EnemyManager::GetEnemyManager().GetNearestEnemy(playerPos);
			if (!target)
			{
				m_isActive = false;
				return;
			}
			targetPos = target->GetLockOnPos();
		}

		m_pos = ConvWorldPosToScreenPos(targetPos);

		VECTOR diff = VSub(targetPos, playerPos);
		float dist = VSize(diff);

		// 距離が範囲外なら無効化
		if (!p->GetIsLockOn() && dist > MARKER_VISIBLE_DISTANCE)
		{
			m_isActive = false;
		}
		else
		{
			m_isActive = true;
		}
	}
}


void Marker::Draw()
{
	if (auto p = m_pPlayer.lock())
	{
		if (p->GetIsLockOn())
		{
			DrawCircleAA(m_pos.x, m_pos.y, 8, 16, GetColor(181, 90, 68), FALSE);
		}
		else
		{
			DrawCircleAA(m_pos.x, m_pos.y, 8, 16, GetColor(204, 200, 175), FALSE);
		}
	}
}