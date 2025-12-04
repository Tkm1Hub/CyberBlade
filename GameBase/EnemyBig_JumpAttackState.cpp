#include "stdafx.h"
#include "EnemyBig.h"
#include "EnemyBig_JumpAttackState.h"
#include "EnemyBig_WarningState.h"
#include "TimeManager.h"

void EnemyBig_JumpAttackState::OnStart()
{
	// 移動速度の設定
	m_pEnemyBig->SetMoveSpeed(0.0f);

	// アニメーションの設定
	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::AttackJump), false);
}

void EnemyBig_JumpAttackState::OnUpdate()
{
	// 攻撃中の移動の更新
	AttackMove();

	// モーションが終わるとWarningに戻す
	if (m_pEnemyBig->animation.GetIsAnimFinished())
	{
		auto spWarningState = std::make_shared<EnemyBig_WarningState>();
		m_pEnemyBig->ChangeState(spWarningState);
		return;
	}
}

void EnemyBig_JumpAttackState::OnExit()
{
}

void EnemyBig_JumpAttackState::AttackMove()
{
	int currentAnimCount = m_pEnemyBig->animation.GetCurrentAnimCount();

	// 溜め動作中
	if (currentAnimCount < JUMP_START_COUNT)
	{
		attackDir = m_pEnemyBig->GetToPlayerDirection();
	}

	// 攻撃有効化（ジャンプ開始
	if (currentAnimCount == JUMP_START_COUNT)
	{
		// 着地地点を設定
		targetPos = m_pEnemyBig->GetPlayerPos();
		targetPos.y = 0.0f;
	}

	// ジャンプ中
	if (currentAnimCount > JUMP_START_COUNT && currentAnimCount < JUMP_END_COUNT)
	{
		// 移動速度を計算
		VECTOR diff = VSub(m_pEnemyBig->GetPosition(), targetPos);
		float dist = VSize(diff);
		attackSpeed = dist / (JUMP_END_COUNT - JUMP_START_COUNT);

		// 高さ(JumpPower)を計算
		float t = (float)(currentAnimCount - JUMP_START_COUNT) / (float)(JUMP_END_COUNT - JUMP_START_COUNT);
		if (t > 0.0f || t < 1.0f)
		{
			float parabola = 4.0f * t * (1.0f - t);
			float jumpPower = m_pEnemyBig->GetParams().AttackJumpMaxHeight * parabola;
		}

	}

	// 着地
	if (currentAnimCount == JUMP_END_COUNT)
	{
		m_pEnemyBig->SetJumpPower(0.0f);

	}

	m_pEnemyBig->SetMoveSpeed(attackSpeed);
	m_pEnemyBig->SetTargetAngle(targetDir);
	m_pEnemyBig->SetMoveVec(dodgeDir);
}