#include "stdafx.h"
#include "Input.h"
#include "Player.h"
#include "Player_FallState.h"
#include "Player_Jump2State.h"
#include "Player_AttackJump1State.h"
#include "Player_DodgeState.h"


void Player_Jump2State::OnStart()
{
	// ジャンプアニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Jump), false);

	// ジャンプ力を加算
	m_pPlayer->SetJumpPower(m_pPlayer->GetParams().Jump2Power);
	// ジャンプフラグを更新
	m_pPlayer->SetIsJumping(true);

	// ジャンプ回数を加算
	m_pPlayer->AddJumpCount();
}

void Player_Jump2State::OnUpdate()
{
	frameCount++;

	// 重力を適応
	if (m_pPlayer->GetCurrentJumpPower() > 0.0f)
	{
		float currentJumpPower = m_pPlayer->GetCurrentJumpPower();
		currentJumpPower -= m_pPlayer->GetParams().Gravity;
		m_pPlayer->SetJumpPower(currentJumpPower);
	}

	// 空中攻撃に移行
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_1)
	{
		auto spAttackJump1State = std::make_shared<Player_AttackJump1State>();
		m_pPlayer->ChangeState(spAttackJump1State);
		return;
	}

	// ジャンプ力が０以下だと落下中
	if (m_pPlayer->GetCurrentJumpPower() < 0.0f)
	{
		auto spFallState = std::make_shared<Player_FallState>();
		m_pPlayer->ChangeState(spFallState);
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

void Player_Jump2State::OnExit()
{

}