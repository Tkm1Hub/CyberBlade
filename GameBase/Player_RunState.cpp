#include "stdafx.h"
#include "Player_RunState.h"
#include "Player_StandState.h"
#include "Player_JumpState.h"
#include "Player_AttackDashState.h"
#include "CameraManager.h"
#include "Player.h"
#include "Input.h"

void Player_RunState::OnStart()
{
	// 走り状態のフラグを立てる
	m_pPlayer->SetRunFlag(true);

	m_pPlayer->SetMoveFlag(true);

	// 速度変更
	float currentMoveSpeed = m_pPlayer->GetParams().RunSpeed;
	m_pPlayer->SetMoveSpeed(currentMoveSpeed);

	// 歩きアニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Run));
}

void Player_RunState::OnUpdate()
{

	// スティック入力がない場合Standに戻る
	if (!Input::GetInput().GetIsMoveLStick())
	{
		auto spStandState = std::make_shared<Player_StandState>();
		m_pPlayer->ChangeState(spStandState);
		return;
	}

	// A（３）ボタンでジャンプ
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
	{
		auto spJumpState = std::make_shared<Player_JumpState>();
		m_pPlayer->ChangeState(spJumpState);
		return;
	}

	// X（１）ボタンでダッシュ攻撃
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_1)
	{
		auto spAttackDashState = std::make_shared<Player_AttackDashState>();
		m_pPlayer->ChangeState(spAttackDashState);
		return;
	}
}

void Player_RunState::OnExit()
{
}