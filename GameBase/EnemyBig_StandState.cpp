#include "stdafx.h"
#include "EnemyBig_StandState.h"
#include "EnemyBig.h"
#include "EnemyBig_AlertState.h"

void EnemyBig_StandState::OnStart()
{
	// 移動ベクトルの初期化
	m_pEnemyBig->SetMoveVec(VGet(0.0f, 0.0f, 0.0f));

	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::Idle), true);
}

void EnemyBig_StandState::OnUpdate()
{
	// 目標角度更新
	m_pEnemyBig->SetTargetAngle(m_pEnemyBig->GetToPlayerDirection());

	if (m_pEnemyBig->IsPlayerInRange(m_pEnemyBig->GetParams().WarningDistance))
	{
		auto spAlertState = std::make_shared<EnemyBig_AlertState>();
		m_pEnemyBig->ChangeState(spAlertState);
		return;
	}
}

void EnemyBig_StandState::OnExit()
{
}