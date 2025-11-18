#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_DamageState.h"
#include "Player_DodgeState.h"
#include "Player_Attack1State.h"
#include "Player_SwordRunState.h"
#include "Player_Attack3State.h"
#include "Player_SlowRunState.h"
#include "Player_StandState.h"
#include "Player_DodgeState.h"
#include "Player_Jump1State.h"


void Player_DamageState::OnStart()
{
	
}

void Player_DamageState::OnUpdate()
{
	frameCount++;
	// ノックバック速度を設定
	m_pPlayer->SetMoveSpeed(m_pPlayer->GetParams().DamageKnockBackSpeed);

	// のけぞり中攻撃ボタンが押されたらフラグを立てる
	if (!isInputAttack && Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_1)
	{
		isInputAttack = true;
	}

	// のけぞり中ジャンプボタンが押されたらフラグを立てる
	if (!isInputJump && Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
	{
		isInputJump = true;
	}

	// のけぞり中回避が押されたらフラグを立てる
	if (!isInputDodge && Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_6)
	{
		isInputDodge = true;
	}

	if (frameCount > 22)
	{
		if (isInputJump)
		{
			auto spJumpState = std::make_shared<Player_Jump1State>();
			m_pPlayer->ChangeState(spJumpState);
			return;
		}

		if (isInputDodge)
		{
			// 回避に移行
			auto spDodgeState = std::make_shared<Player_DodgeState>();
			m_pPlayer->ChangeState(spDodgeState);
			return;
		}

		if (isInputAttack)
		{
			auto spAttack1State = std::make_shared<Player_Attack1State>();
			m_pPlayer->ChangeState(spAttack1State);
			return;
		}

		// スティック入力があれば走り状態に変更
		if (Input::GetInput().GetIsMoveLStick())
		{
			auto spSlowRunState = std::make_shared<Player_SlowRunState>();
			m_pPlayer->ChangeState(spSlowRunState);
			return;
		}
		else
		{
			auto spStandState = std::make_shared<Player_StandState>();
			m_pPlayer->ChangeState(spStandState);
			return;
		}
	}
}

void Player_DamageState::OnExit()
{
	m_pPlayer->SetDamageFlag(false);
}