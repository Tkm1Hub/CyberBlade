#include "stdafx.h"
#include "EnemyBig.h"
#include "EnemyBig_Slash2State.h"
#include "EnemyBig_WarningState.h"
#include "EnemyBig_DamageState.h"
#include "EffectManager.h"

void EnemyBig_Slash2State::OnStart()
{
	// 移動速度の設定
	m_pEnemyBig->SetMoveSpeed(0.0f);

	// アニメーションの設定
	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::Slash2), false);

	// エフェクト再生
	EffectManager::GetInstance().PlayEffect("Attack_Warning", m_pEnemyBig->GetHeadPos());
}

void EnemyBig_Slash2State::OnUpdate()
{
	// 攻撃中の移動の更新
	AttackMove();

	// 攻撃モーションが終わるとWarningに戻す
	if (m_pEnemyBig->animation.GetIsAnimFinished())
	{
		auto spWarningState = std::make_shared<EnemyBig_WarningState>();
		m_pEnemyBig->ChangeState(spWarningState);
		return;
	}
}

void EnemyBig_Slash2State::OnExit()
{
	// 攻撃フラグ
	m_pEnemyBig->SetAttackFrag(false);
}

void EnemyBig_Slash2State::AttackMove()
{
	int currentAnimCount = m_pEnemyBig->animation.GetCurrentAnimCount();

	// 溜め動作中
	if (currentAnimCount < ATTACK_ACTIVE_COUNT)
	{
		attackDir = m_pEnemyBig->GetToPlayerDirection();
	}

	// 攻撃有効化
	if (currentAnimCount == ATTACK_ACTIVE_COUNT)
	{
		m_pEnemyBig->SetAttackFrag(true);
		attackSpeed = m_pEnemyBig->GetParams().AttackMoveSpeed;
	}

	// 攻撃中
	if (currentAnimCount > ATTACK_ACTIVE_COUNT && currentAnimCount < ATTACK_DISABLE_COUNT)
	{
		attackSpeed -= ATTACK_SPEED_DECEL;
	}

	// 攻撃終了
	if (currentAnimCount == ATTACK_DISABLE_COUNT)
	{
		attackSpeed = 0.0f;
		m_pEnemyBig->SetAttackFrag(false);
	}

	m_pEnemyBig->SetMoveSpeed(attackSpeed);
	m_pEnemyBig->SetTargetAngle(attackDir);
	m_pEnemyBig->SetMoveVec(attackDir);
}