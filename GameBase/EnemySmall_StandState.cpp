#include "stdafx.h"
#include "EnemySmall_StandState.h"
#include "EnemySmall_ChaseState.h"
#include "EnemySmallDamageState.h"
#include "EnemySmall.h"

void EnemySmall_StandState::OnStart()
{
	// 移動ベクトルの初期化
	m_pEnemySmall->SetMoveVec(VGet(0.0f, 0.0f, 0.0f));

}

void EnemySmall_StandState::OnUpdate()
{
	bool damageFlag = m_pEnemySmall->GetDamageFlag();

	// プレイヤーが追跡開始範囲内かつ、攻撃開始範囲外の場合追跡
	if (m_pEnemySmall->IsPlayerInRange(m_pEnemySmall->GetParams().ChaseTriggerDistance)
		&& !m_pEnemySmall->IsPlayerInRange(m_pEnemySmall->GetParams().AttackTriggerDistance))
	{
		auto spChaseState = std::make_shared<EnemySmall_ChaseState>();
		m_pEnemySmall->ChangeState(spChaseState);
		return;
	}

	// ダメージを食らったらステート変更
	if (damageFlag)
	{
		auto spDamageState = std::make_shared<EnemySmall_DamageState>();
		m_pEnemySmall->ChangeState(spDamageState);
		return;
	}
}

void EnemySmall_StandState::OnExit()
{

}