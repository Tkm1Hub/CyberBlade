#include "stdafx.h"
#include "Input.h"
#include "Player.h"
#include "Player_FallState.h"
#include "Player_Jump2State.h"
#include "Player_AttackJump1State.h"
#include "Player_DodgeState.h"
#include "Player_StandState.h"


void Player_FallState::OnStart()
{
	// 落下アニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Fall),true);

	// 最大移動速度を設定
	m_pPlayer->SetCurrentMaxSpeed(m_pPlayer->GetParams().FallMaxMoveSpeed);
}

void Player_FallState::OnUpdate()
{
	if (!m_pPlayer->GetIsJumping())
	{
		auto spStandState = std::make_shared<Player_StandState>();
		m_pPlayer->ChangeState(spStandState);
		return;
	}

	// 重力を適応
	float currentJumpPower = m_pPlayer->GetCurrentJumpPower();
	currentJumpPower -= m_pPlayer->GetParams().Gravity;
	m_pPlayer->SetJumpPower(currentJumpPower);

	// ジャンプ2に移行
	if (m_pPlayer->GetCurrentJumpCount() < m_pPlayer->GetParams().JUMP_MAX_COUNT)
	{
		if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
		{
			auto spJumpState = std::make_shared<Player_Jump2State>();
			m_pPlayer->ChangeState(spJumpState);
			return;
		}
	}

	// 空中攻撃に移行
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_1)
	{
		auto spAttackJump1State = std::make_shared<Player_AttackJump1State>();
		m_pPlayer->ChangeState(spAttackJump1State);
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

void Player_FallState::OnExit()
{

}