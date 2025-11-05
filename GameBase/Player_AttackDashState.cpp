#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_AttackDashState.h"
#include "Player_Attack3State.h"
#include "Player_RunState.h"
#include "Player_StandState.h"
#include "Player_DodgeState.h"
#include "Player_JumpState.h"


void Player_AttackDashState::OnStart()
{
	m_pPlayer->SetAttackFrag(true);

	// アニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::AttackDash),false);

	moveSpeed = m_pPlayer->GetParams().AttackDashMoveSpeed;

}

void Player_AttackDashState::OnUpdate()
{
	frameCount++;

	if (!m_doNextAttack)
	{
		if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_1)
		{
			m_doNextAttack = true;
		}
	}


	if (frameCount >= 20)
	{
		if (m_doNextAttack)
		{
			auto spAttack3State = std::make_shared<Player_Attack3State>();
			m_pPlayer->ChangeState(spAttack3State);
		}

		if (frameCount >= 30)
		{
			if (Input::GetInput().GetIsMoveLStick())
			{
				auto spWalkState = std::make_shared<Player_RunState>();
				m_pPlayer->ChangeState(spWalkState);	// スティック入力があれば走りに戻す
				return;
			}
			else if (!Input::GetInput().GetIsMoveLStick())
			{
				auto spStandState = std::make_shared<Player_StandState>();
				m_pPlayer->ChangeState(spStandState);	// スティック入力がなければ立ち止まりに戻す
				return;
			}
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

void Player_AttackDashState::OnExit()
{
	m_pPlayer->SetAttackFrag(false);
}