#include "stdafx.h"
#include "EnemySmall_ChaseState.h"
#include "EnemySmall_StandState.h"
#include "EnemySmall.h"

void EnemySmall_ChaseState::OnStart()
{
	// 移動速度を設定
	m_pEnemySmall->SetMoveSpeed(m_pEnemySmall->GetParams().ChaseSpeed);
}

void EnemySmall_ChaseState::OnUpdate()
{
	// 移動ベクトルをプレイヤーの方向に設定
	VECTOR dir = m_pEnemySmall->GetToPlayerDirection();
	m_pEnemySmall->SetMoveVec(dir);

	// プレイヤーが一定範囲内に入ったらStandに戻す
	if (m_pEnemySmall->IsPlayerInRange(m_pEnemySmall->GetParams().AttackTriggerDistance))
	{
		auto spStandState = std::make_shared<EnemySmall_StandState>();
		m_pEnemySmall->ChangeState(spStandState);
		return;
	}

	// プレイヤーが範囲外だと追跡をやめる
	if (!m_pEnemySmall->IsPlayerInRange(m_pEnemySmall->GetParams().ChaseTriggerDistance))
	{
		auto spStandState = std::make_shared<EnemySmall_StandState>();
		m_pEnemySmall->ChangeState(spStandState);
		return;
	}

}

void EnemySmall_ChaseState::OnExit()
{
}