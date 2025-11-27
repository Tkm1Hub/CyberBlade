#include "stdafx.h"
#include "EnemyBig_StandState.h"
#include "EnemyBig.h"

void EnemyBig_StandState::OnStart()
{
	// ˆÚ“®ƒxƒNƒgƒ‹‚Ì‰Šú‰»
	m_pEnemyBig->SetMoveVec(VGet(0.0f, 0.0f, 0.0f));

	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::Idle), true);

}

void EnemyBig_StandState::OnUpdate()
{
}

void EnemyBig_StandState::OnExit()
{

}