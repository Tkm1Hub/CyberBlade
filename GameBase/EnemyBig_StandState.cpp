#include "stdafx.h"
#include "EnemyBig_StandState.h"
#include "EnemyBig.h"
#include "EnemyBig_WarningState.h"

void EnemyBig_StandState::OnStart()
{
	// ˆÚ“®ƒxƒNƒgƒ‹‚Ì‰Šú‰»
	m_pEnemyBig->SetMoveVec(VGet(0.0f, 0.0f, 0.0f));

	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::Idle), true);
}

void EnemyBig_StandState::OnUpdate()
{
	if (m_pEnemyBig->IsPlayerInRange(m_pEnemyBig->GetParams().WarningDistance))
	{
		auto spWarningState = std::make_shared<EnemyBig_WarningState>();
		m_pEnemyBig->ChangeState(spWarningState);
		return;
	}
}

void EnemyBig_StandState::OnExit()
{
}