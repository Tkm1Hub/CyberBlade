#include "stdafx.h"
#include "EnemyBig.h"
#include "EnemyBig_DamageState.h"
#include "EnemyBig_StandState.h"

void EnemyBig_DamageState::OnStart()
{
	m_moveSpeed = m_pEnemyBig->GetParams().DamageSpeed;


}

void EnemyBig_DamageState::OnUpdate()
{
	m_frameCount++;
	// ノックバック速度を設定
	m_pEnemyBig->SetMoveSpeed(m_moveSpeed);
	m_pEnemyBig->SetMoveVec(m_pEnemyBig->GetKnockBackDir());

	if (m_frameCount > 25)
	{
		auto spStandState = std::make_shared<EnemyBig_StandState>();
		m_pEnemyBig->ChangeState(spStandState);
		return;
	}
}

void EnemyBig_DamageState::OnExit()
{
	m_pEnemyBig->SetDamageFlag(false);
}
