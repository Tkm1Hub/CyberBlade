#include "stdafx.h"
#include "EnemySmall.h"
#include "EnemySmall_FallState.h"

void EnemySmall_FallState::OnStart()
{

}

void EnemySmall_FallState::OnUpdate()
{
	// d—Í‚ð“K‰ž
	float currentJumpPower = m_pEnemySmall->GetCurrentJumpPower();
	currentJumpPower -= m_pEnemySmall->GetParams().Gravity;
	m_pEnemySmall->SetJumpPower(currentJumpPower);
}

void EnemySmall_FallState::OnExit()
{

}