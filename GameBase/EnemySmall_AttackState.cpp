#include "stdafx.h"
#include "EnemySmall.h"
#include "EnemySmall_AttackState.h"
#include "EnemySmall_StandState.h"
#include "EnemySmallDamageState.h"

void EnemySmall_AttackState::OnStart()
{
	// 移動速度の設定
	m_pEnemySmall->SetMoveSpeed(m_pEnemySmall->GetParams().AttackMoveSpeed);

	// アニメーションの設定
	m_pEnemySmall->animation.Play(static_cast<int>(EnemySmallAnimState::Attack), false);

	// 攻撃フラグ
	m_pEnemySmall->SetAttackFrag(true);
}

void EnemySmall_AttackState::OnUpdate()
{
	// 移動ベクトルをプレイヤーの方向に設定
	VECTOR dir = m_pEnemySmall->GetToPlayerDirection();
	m_pEnemySmall->SetMoveVec(dir);

	// 攻撃モーションが終わるとStandに戻す
	if (m_pEnemySmall->animation.GetIsAnimFinished())
	{
		auto spStandState = std::make_shared<EnemySmall_StandState>();
		m_pEnemySmall->ChangeState(spStandState);
		return;
	}

	// ダメージを食らったらステート変更
	if (m_pEnemySmall->GetDamageFlag())
	{
		auto spDamageState = std::make_shared<EnemySmall_DamageState>();
		m_pEnemySmall->ChangeState(spDamageState);
		return;
	}
}

void EnemySmall_AttackState::OnExit()
{
	// 攻撃フラグ
	m_pEnemySmall->SetAttackFrag(false);
}