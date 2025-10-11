#include "stdafx.h"
#include "Player_WalkState.h"
#include "Player_StandState.h"
#include "Player_JumpState.h"
#include "Player_RunState.h"
#include "Player_Attack1State.h"
#include "CameraManager.h"
#include "Player.h"
#include "Input.h"

void Player_WalkState::OnStart()
{
	// 歩きアニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Walk));

	m_pPlayer->SetMoveFlag(true);
}

void Player_WalkState::OnUpdate()
{
	// スティック入力がない場合Standに戻る
	if (!Input::GetInput().GetIsMoveLStick())
	{
		auto spStandState = std::make_shared<Player_StandState>();
		m_pPlayer->ChangeState(spStandState);
		return;
	}

	// RT（8）ボタンでダッシュ
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_6)
	{
		auto spRunState = std::make_shared<Player_RunState>();
		m_pPlayer->ChangeState(spRunState);
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

void Player_WalkState::OnExit()
{
	m_pPlayer->SetMoveFlag(false);
}

