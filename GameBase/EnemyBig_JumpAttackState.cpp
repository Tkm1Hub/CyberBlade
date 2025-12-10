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
		// 開始位置を固定
		VECTOR startPos = m_pEnemyBig->GetPosition();

		// 着地位置を固定（この瞬間のプレイヤー位置）
		targetPos = m_pEnemyBig->GetPlayerPos();

		// 方向を正しく固定
		VECTOR diff = VSub(targetPos, startPos);
		float dist = VSize(diff);

		attackDir = VNorm(diff);      // 方向決定
		float jumpFrames = JUMP_END_COUNT - JUMP_START_COUNT;

		attackSpeed = dist / jumpFrames;

		prevJumpHeight = 0.0f;
	}

	// ジャンプ中
	if (currentAnimCount > JUMP_START_COUNT && currentAnimCount < JUMP_END_COUNT)
	{
		// 高さ(JumpPower)を計算
		float t = (currentAnimCount - JUMP_START_COUNT) / (JUMP_END_COUNT - JUMP_START_COUNT);
		float parabola = 4.0f * t * (1.0f - t);
		float newHeight = m_pEnemyBig->GetParams().AttackJumpMaxHeight * parabola;

		// y速度 = 高さの差分
		float jumpVelocity = newHeight - prevJumpHeight;

		m_pEnemyBig->SetJumpPower(jumpVelocity);

		// 次フレーム用に保持
		prevJumpHeight = newHeight;
	}

	// 着地
	if (currentAnimCount == JUMP_END_COUNT)
	{
		attackSpeed = 0.0f;
	}

	m_pEnemyBig->SetMoveSpeed(attackSpeed);
	m_pEnemyBig->SetTargetAngle(attackDir);
	m_pEnemyBig->SetMoveVec(attackDir);
}