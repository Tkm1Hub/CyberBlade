#include "stdafx.h"
#include "Marker.h"
#include "EnemyBase.h"
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
		auto target = p->GetLockOnTarget();
		VECTOR targetPos = target->GetPosition();

		m_pos = ConvWorldPosToScreenPos(target->GetPosition());

		VECTOR diff = VSub(targetPos, playerPos);
		float dist = VSize(diff);

		// ‹——£‚ª”ÍˆÍŠO‚È‚ç–³Œø‰»
		if (dist < MARKER_VISIBLE_DISTANCE)
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
	DrawCircleAA(m_pos.x, m_pos.z, 3, 16, GetColor(204, 200, 175), FALSE);
}