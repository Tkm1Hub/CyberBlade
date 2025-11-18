#include "stdafx.h"
#include "Player_RunState.h"
#include "Player_StandState.h"
#include "Player_Jump1State.h"
#include "Player_AttackDashState.h"
#include "Player.h"
#include "Player_DodgeState.h"
#include "Input.h"
#include "Player_FallState.h"
#include "Player_DamageState.h"


void Player_RunState::OnStart()
{
	// 走り状態のフラグを立てる
	m_pPlayer->SetRunFlag(true);

	m_pPlayer->SetMoveFlag(true);

	// 速度変更
	float currentMoveSpeed = m_pPlayer->GetParams().RunSpeed;
	m_pPlayer->SetMoveSpeed(currentMoveSpeed);
	m_pPlayer->SetCurrentMaxSpeed(m_pPlayer->GetParams().RunSpeed);

	// 歩きアニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Run),true);
}

void Player_RunState::OnUpdate()
{

	// ダメージを食らったら状態変更
	if (m_pPlayer->GetDamageFlag())
	{
		auto spDamageState = std::make_shared<Player_DamageState>();
		m_pPlayer->ChangeState(spDamageState);
		return;
	}

	// 空中にいれば落下に移行
	if (m_pPlayer->GetIsJumping())
	{
		auto spFallState = std::make_shared<Player_FallState>();
		m_pPlayer->ChangeState(spFallState);
		return;
	}

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
		auto spJumpState = std::make_shared<Player_Jump1State>();
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

	// R（8）ボタンで回避
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_6)
	{
		auto spDodgeState = std::make_shared<Player_DodgeState>();
		m_pPlayer->ChangeState(spDodgeState);
		return;
	}
}

void Player_RunState::OnExit()
{
	m_pPlayer->SetRunFlag(false);
}