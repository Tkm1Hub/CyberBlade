#include "stdafx.h"
#include "EnemyBig_ChaseState.h"
#include "EnemyBig_StandState.h"
#include "EnemyBig_AttackState.h"
#include "EnemyBig.h"

void EnemyBig_ChaseState::OnStart()
{
	// 移動速度を設定
	m_pEnemyBig->SetMoveSpeed(m_pEnemyBig->GetParams().ChaseSpeed);
	// アニメ再生
	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::Chase), true);
	//警戒フラグ
	m_pEnemyBig->SetIsAlert(true);
}

void EnemyBig_ChaseState::OnUpdate()
{
	// 移動ベクトルをプレイヤーの方向に設定
	VECTOR dir = m_pEnemyBig->GetToPlayerDirection();
	m_pEnemyBig->SetMoveVec(dir);

	// プレイヤーが一定範囲内に入ったら攻撃
	if (m_pEnemyBig->IsPlayerInRange(m_pEnemyBig->GetParams().AttackTriggerDistance))
	{
		auto spAttackState = std::make_shared<EnemyBig_AttackState>();
		m_pEnemyBig->ChangeState(spAttackState);
		return;
	}

	//// プレイヤーが範囲外だと追跡をやめる
	//if (!m_pEnemyBig->IsPlayerInRange(m_pEnemyBig->GetParams().ChaseTriggerDistance))
	//{
	//	//警戒フラグ
	//	m_pEnemyBig->SetIsAlert(false);

	//	auto spStandState = std::make_shared<EnemyBig_StandState>();
	//	m_pEnemyBig->ChangeState(spStandState);
	//	return;
	//}

}

void EnemyBig_ChaseState::OnExit()
{
}