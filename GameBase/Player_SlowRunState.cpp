#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_SlowRunState.h"
#include "Player_WalkState.h"
#include "Player_StandState.h"
#include "Player_Jump1State.h"
#include "Player_SlowRunState.h"
#include "Player_Attack1State.h"
#include "Player_FallState.h"
#include "Player_DodgeState.h"
#include "Player_DamageState.h"




void Player_SlowRunState::OnStart()
{
	// アニメーション再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::SlowRun),true);
	// 移動フラグを立てる
	m_pPlayer->SetMoveFlag(true);
	// 移動速度を設定
	m_pPlayer->SetMoveSpeed(m_pPlayer->GetParams().SlowRunSpeed);
	m_pPlayer->SetCurrentMaxSpeed(m_pPlayer->GetParams().SlowRunSpeed);
}

void Player_SlowRunState::OnUpdate()
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

	// スティックの傾きが一定数以下で歩き状態に変更
	if (Input::GetInput().GetLeftStickPower() <= m_pPlayer->GetParams().StickTiltSlowRun - m_pPlayer->GetParams().StickMargin)
	{
		auto spWalkState = std::make_shared<Player_WalkState>();
		m_pPlayer->ChangeState(spWalkState);
		return;
	}

	// R（8）ボタンで回避
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_6)
	{
		auto spDodgeState = std::make_shared<Player_DodgeState>();
		m_pPlayer->ChangeState(spDodgeState);
		return;
	}

	// A（３）ボタンでジャンプ
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
	{
		auto spJumpState = std::make_shared<Player_Jump1State>();
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

void Player_SlowRunState::OnExit()
{
	m_pPlayer->SetMoveFlag(false);
}

