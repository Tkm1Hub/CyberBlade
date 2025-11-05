#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_Attack1State.h"
#include "Player_Attack2State.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"
#include "Player_DodgeState.h"
#include "Player_JumpState.h"
#include "Player_FallState.h"

void Player_Attack1State::OnStart()
{
	m_pPlayer->SetAttackFrag(true);

	// 攻撃１アニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::AttackJump1),false);

	moveSpeed = m_pPlayer->GetParams().Attack1MoveSpeed;

}

void Player_Attack1State::OnUpdate()
{
	frameCount++;

	// 攻撃の方向ベクトルを適用
	VECTOR moveVec = m_pPlayer->GetAttackDir();
	m_pPlayer->SetTargetMoveDirection(moveVec);

	if (moveSpeed > 0.0f) moveSpeed -= 0.02f;
	moveSpeed = max(moveSpeed, 0.0f);
	m_pPlayer->SetMoveSpeed(moveSpeed);

	if (!isInputAttack)
	{
		if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_1)
		{
			isInputAttack = true;
		}
	}

	// 攻撃の待機時間経過
	if (frameCount >= m_pPlayer->GetParams().ATTACK_1_NEXT_ATTACK_WAIT_FRAMES)
	{
		// 空中にいる場合
		if (m_pPlayer->GetIsJumping())
		{

		}
		else
		{
			// 地上にいる場合
			if (isInputAttack)
			{
				auto spAttack2State = std::make_shared<Player_Attack2State>();
				m_pPlayer->ChangeState(spAttack2State);	// 次の攻撃に移行
				return;
			}
		}

	}

	// 移動硬直終了
	if (frameCount >= m_pPlayer->GetParams().ATTACK_1_RECOVERY_FRAMES)
	{
		// 空中にいれば落下に移行
		if (m_pPlayer->GetIsJumping())
		{
			auto spFallState = std::make_shared<Player_FallState>();
			m_pPlayer->ChangeState(spFallState);
			return;
		}

		if (Input::GetInput().GetIsMoveLStick())
		{
			auto spWalkState = std::make_shared<Player_WalkState>();
			m_pPlayer->ChangeState(spWalkState);	// スティック入力があれば歩きに戻す
			return;
		}

		// アニメの再生が終わったら
		if (m_pPlayer->animation.GetIsAnimFinished())
		{
			auto spStandState = std::make_shared<Player_StandState>();
			m_pPlayer->ChangeState(spStandState);	// スティック入力がなければ立ち止まりに戻す
			return;
		}
	}

	// A（３）ボタンでジャンプ
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
	{
		auto spJumpState = std::make_shared<Player_JumpState>();
		m_pPlayer->ChangeState(spJumpState);
		return;
	}

	// R（8）ボタンで回避
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_6)
	{
		auto spDodgeState = std::make_shared<Player_DodgeState>();
		m_pPlayer->ChangeState(spDodgeState);
		return;
	}
}

void Player_Attack1State::OnExit()
{
	m_pPlayer->SetAttackFrag(false);
}