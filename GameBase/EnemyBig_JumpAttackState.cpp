#include "stdafx.h"
#include "EnemyBig.h"
#include "EnemyBig_JumpAttackState.h"
#include "EnemyBig_WarningState.h"
#include "TimeManager.h"
#include "EffectManager.h"

void EnemyBig_JumpAttackState::OnStart()
{
	// 着地位置を固定（この瞬間のプレイヤー位置）
	targetPos = m_pEnemyBig->GetPlayerPos();
	targetPos.y = 0.0f;

	// 移動速度の設定
	m_pEnemyBig->SetMoveSpeed(0.0f);

	// アニメーションの設定
	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::AttackJump), false);

	// エフェクト再生
	EffectManager::GetInstance().PlayEffect("Attack_Warning", m_pEnemyBig->GetHeadPos());
}

void EnemyBig_JumpAttackState::OnUpdate()
{
	// 攻撃中の移動の更新
	AttackMove();

	// 攻撃の当たり判定更新
	VECTOR AtkCollPos = m_pEnemyBig->GetHipPos();
	m_pEnemyBig->SetAttackCollisionPos(AtkCollPos);
	m_pEnemyBig->SetAttackCollisionRadius(m_pEnemyBig->GetParams().HipHitRadius);

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
	m_pEnemyBig->SetAttackFrag(false);
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
		startPos.y = 0.0f;


		// 方向を正しく固定
		VECTOR diff = VSub(targetPos, startPos);
		float dist = VSize(diff);

		attackDir = VNorm(diff);      // 方向決定
		float jumpFrames = JUMP_END_COUNT - JUMP_START_COUNT;

		attackSpeed = dist / jumpFrames;
		attackSpeed *= 0.5f;

		m_pEnemyBig->SetJumpPower(m_pEnemyBig->GetParams().AttackJumpPower);

		m_pEnemyBig->SetIsJumping(true);

		//エフェクト再生
		EffectManager::GetInstance().PlayEffect("Boss_JumpWave", m_pEnemyBig->GetPosition());
	}

	// ジャンプ中
	if (currentAnimCount > JUMP_START_COUNT && currentAnimCount < JUMP_END_COUNT)
	{
		// 高さ(JumpPower)を計算

	}

	// 着地
	if (currentAnimCount == JUMP_END_COUNT)
	{
		attackSpeed = 0.0f;
		m_pEnemyBig->SetAttackFrag(true);
		// エフェクト再生
		EffectManager::GetInstance().PlayEffect("Boss_ShockWave",m_pEnemyBig->GetPosition());
	}

	// 攻撃無効化
	if (currentAnimCount == ATTACK_DISABLE_COUNT)
	{
		m_pEnemyBig->SetAttackFrag(false);
	}

	m_pEnemyBig->SetMoveSpeed(attackSpeed);
	m_pEnemyBig->SetTargetAngle(attackDir);
	m_pEnemyBig->SetMoveVec(attackDir);
}