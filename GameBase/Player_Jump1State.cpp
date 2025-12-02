#include "stdafx.h"
#include "Input.h"
#include "Player.h"
#include "Player_FallState.h"
#include "Player_Jump1State.h"
#include "Player_Jump2State.h"
#include "Player_AttackJump1State.h"
#include "Player_DodgeState.h"
#include "Player_DamageState.h"
#include "TimeManager.h"


void Player_Jump1State::OnStart()
{
	// ジャンプアニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Jump1),false);

}

void Player_Jump1State::OnUpdate()
{
	frameCount++;

	// フレーム遅延を入れてからジャンプ力を加算
	if (frameCount == m_pPlayer->GetParams().JUMP_START_WAIT_FRAMES)
	{
		// ジャンプ力を加算
		m_pPlayer->SetJumpPower(m_pPlayer->GetParams().Jump1Power);
		// ジャンプフラグを更新
		m_pPlayer->SetIsJumping(true);
		// ジャンプ回数を加算
		m_pPlayer->AddJumpCount();
	}

	// ダメージを食らったら状態変更
	if (m_pPlayer->GetDamageFlag())
	{
		auto spDamageState = std::make_shared<Player_DamageState>();
		m_pPlayer->ChangeState(spDamageState);
		return;
	}

	if (frameCount > m_pPlayer->GetParams().JUMP_START_WAIT_FRAMES)
	{
		// ジャンプボタンが押されたか
		if (!isInputJump && Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
		{
			isInputJump = true;
		}
	}
	
	if (frameCount >= m_pPlayer->GetParams().JUMP_1_TO_2_WAIT_FRAMES)
	{
		if (isInputJump)
		{
			auto spJumpState = std::make_shared<Player_Jump2State>();
			m_pPlayer->ChangeState(spJumpState);
			return;
		}
	}

	// 重力を適応
	if (m_pPlayer->GetCurrentJumpPower() > 0.0f)
	{
		float currentJumpPower = m_pPlayer->GetCurrentJumpPower();
		currentJumpPower -= m_pPlayer->GetParams().Gravity * TimeManager::GetInstance().GetTimeScale();
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

void Player_Jump1State::OnExit()
{

}