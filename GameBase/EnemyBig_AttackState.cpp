#include "stdafx.h"
#include "EnemyBig.h"
#include "EnemyBig_AttackState.h"
#include "EnemyBig_StandState.h"
#include "EnemyBig_DamageState.h"

void EnemyBig_AttackState::OnStart()
{
	// 移動速度の設定
	m_pEnemyBig->SetMoveSpeed(m_pEnemyBig->GetParams().AttackMoveSpeed);

	// アニメーションの設定
	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::Attack), false);

	// 攻撃フラグ
	m_pEnemyBig->SetAttackFrag(true);
}

void EnemyBig_AttackState::OnUpdate()
{
	// 移動ベクトルをプレイヤーの方向に設定
	VECTOR dir = m_pEnemyBig->GetToPlayerDirection();
	m_pEnemyBig->SetMoveVec(dir);

	// 攻撃モーションが終わるとStandに戻す
	if (m_pEnemyBig->animation.GetIsAnimFinished())
	{
		auto spStandState = std::make_shared<EnemyBig_StandState>();
		m_pEnemyBig->ChangeState(spStandState);
		return;
	}

	// ダメージを食らったらステート変更
	if (m_pEnemyBig->GetDamageFlag())
	{
		auto spDamageState = std::make_shared<EnemyBig_DamageState>();
		m_pEnemyBig->ChangeState(spDamageState);
		return;
	}
}

void EnemyBig_AttackState::OnExit()
{
	// 攻撃フラグ
	m_pEnemyBig->SetAttackFrag(false);
}