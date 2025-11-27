#include "stdafx.h"
#include "EnemyBig.h"
#include "EnemyBig_FallState.h"

void EnemyBig_FallState::OnStart()
{

}

void EnemyBig_FallState::OnUpdate()
{
	// d—Í‚ð“K‰ž
	float currentJumpPower = m_pEnemyBig->GetCurrentJumpPower();
	currentJumpPower -= m_pEnemyBig->GetParams().Gravity;
	m_pEnemyBig->SetJumpPower(currentJumpPower);
}

void EnemyBig_FallState::OnExit()
{

}