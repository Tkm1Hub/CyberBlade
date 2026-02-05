#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_DamageState.h"
#include "Player_DodgeState.h"
#include "Player_DeathState.h"
#include "Player_Attack1State.h"
#include "Player_SwordRunState.h"
#include "Player_Attack3State.h"
#include "Player_SlowRunState.h"
#include "Player_StandState.h"
#include "Player_Jump1State.h"
#include "TimeManager.h"
#include "Sound.h"

void Player_DamageState::OnStart()
{
	moveSpeed = m_pPlayer->GetParams().DamageKnockBackSpeed;
	TimeManager::GetInstance().SetTimeScale(0.0f);
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Damage), false);
	SoundManager::GetInstance().Play_Sound("SE_Player_Damage");
}

void Player_DamageState::OnUpdate()
{
	if (m_pPlayer->GetIsDead())
	{
		auto spDeathState = std::make_shared<Player_DeathState>();
		m_pPlayer->ChangeState(spDeathState);
		return;
	}

	frameCount++;
	// ノックバック速度を設定
	moveSpeed -= frameCount * DECEL;
	moveSpeed = std::clamp(moveSpeed, 0.0f, m_pPlayer->GetParams().DamageKnockBackSpeed);

	// だんだん加速
	timeScale += frameCount * ACCEL;
	timeScale = std::clamp(timeScale, 0.0f, 1.0f);
	TimeManager::GetInstance().SetTimeScale(timeScale);

	// 重力を適応
	float currentJumpPower = m_pPlayer->GetCurrentJumpPower();
	currentJumpPower -= m_pPlayer->GetParams().Gravity * TimeManager::GetInstance().GetTimeScale();
	m_pPlayer->SetJumpPower(currentJumpPower);


	VECTOR targetPos = m_pPlayer->GetDamageSourcePos();
	targetPos = VSub(targetPos, m_pPlayer->GetPosition());
	targetPos = VNorm(targetPos);

	m_pPlayer->SetTargetMoveDirection(targetPos);
	m_pPlayer->SetMoveSpeed(moveSpeed);


	if (m_pPlayer->animation.GetIsAnimFinished())
	{
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
	TimeManager::GetInstance().SetTimeScale(1.0f);
}