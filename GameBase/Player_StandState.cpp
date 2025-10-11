#include "stdafx.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"
#include "Player_JumpState.h"
#include "Player_Attack1State.h"
#include "Player.h"
#include "Input.h"

void Player_StandState::OnStart()
{
	// 移動ベクトルの初期化
	m_pPlayer->SetMoveVec(VGet(0.0f, 0.0f, 0.0f));

	// 走り状態のフラグを解除
	m_pPlayer->SetRunFlag(false);
	m_pPlayer->SetMoveFlag(false);

	// アイドルアニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Idle));
}

void Player_StandState::OnUpdate()
{
	// 左スティックが入力中なら移動
	if (Input::GetInput().GetIsMoveLStick())
	{
		auto spWalkState = std::make_shared<Player_WalkState>();
		m_pPlayer->ChangeState(spWalkState);
		return;
	}

	// A（３）ボタンでジャンプ
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
	{
		auto spJumpState = std::make_shared<Player_JumpState>();
		m_pPlayer->ChangeState(spJumpState);
		return;
	}

	// X（１）ボタンで攻撃
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_1)
	{
		auto spAttack1State = std::make_shared<Player_Attack1State>();
		m_pPlayer->ChangeState(spAttack1State);
		return;
	}

}

void Player_StandState::OnExit()
{

}