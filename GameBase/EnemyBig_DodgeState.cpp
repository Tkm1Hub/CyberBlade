#include "stdafx.h"
#include "EnemyBig.h"
#include "EnemyBig_DodgeState.h"
#include "EnemyBig_WarningState.h"
#include "EnemyBig_DamageState.h"
#include "TimeManager.h"

void EnemyBig_DodgeState::OnStart()
{
	// 移動速度の設定
	m_pEnemyBig->SetMoveSpeed(0.0f);

	// アニメーションの設定
	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::Dodge), false);
}

void EnemyBig_DodgeState::OnUpdate()
{
	// 攻撃中の移動の更新
	DodgeMove();

	// モーションが終わるとWarningに戻す
	if (m_pEnemyBig->animation.GetIsAnimFinished())
	{
		auto spWarningState = std::make_shared<EnemyBig_WarningState>();
		m_pEnemyBig->ChangeState(spWarningState);
		return;
	}
}

void EnemyBig_DodgeState::OnExit()
{
}

void EnemyBig_DodgeState::DodgeMove()
{
	int currentAnimCount = m_pEnemyBig->animation.GetCurrentAnimCount();

	// 常にプレイヤーを向く
	targetDir = m_pEnemyBig->GetToPlayerDirection();

	// 回避有効化
	if (currentAnimCount == DODGE_ACTIVE_COUNT)
	{
		//m_pEnemyBig->SetIsJumping(true);
		m_pEnemyBig->SetJumpPower(m_pEnemyBig->GetParams().DodgeJumpPower);
		dodgeSpeed = m_pEnemyBig->GetParams().DodgeMoveSpeed;
		
		VECTOR toPlayer = m_pEnemyBig->GetToPlayerDirection();
		dodgeDir = CulcDodgeDir(toPlayer);
	}

	// 攻撃中
	if (currentAnimCount > DODGE_ACTIVE_COUNT && currentAnimCount < DODGE_DISABLE_COUNT)
	{
		dodgeSpeed -= DODGE_SPEED_DECEL;
	}

	// 攻撃終了
	if (currentAnimCount == DODGE_DISABLE_COUNT)
	{
		dodgeSpeed = 0.0f;
	}

	m_pEnemyBig->SetMoveSpeed(dodgeSpeed);
	m_pEnemyBig->SetTargetAngle(targetDir);
	m_pEnemyBig->SetMoveVec(dodgeDir);
}

VECTOR EnemyBig_DodgeState::CulcDodgeDir(VECTOR& DirToPlayer)
{
	// プレイヤーへの方向ベクトルを反転
	VECTOR baseDir = VScale(DirToPlayer, -1.0f);

	// ±90度以内でランダムに回転
	float maxAngle = DX_PI_F / 2.0f;	// 90度
	float rand01 = (float)GetRand(10000) / 10000.0f; // 0～1
	float theta = (rand01 * 2.0f - 1.0f) * maxAngle;  // -90°～+90°

	float c = cosf(theta);
	float s = sinf(theta);

	VECTOR r;
	r.x = baseDir.x * c - baseDir.z * s;
	r.y = 0.0f;
	r.z = baseDir.x * s + baseDir.z * c;

	// 正規化して返す
	return VNorm(r);
}