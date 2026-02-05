#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_DeathState.h"
#include "Player_DodgeState.h"
#include "Player_Attack1State.h"
#include "Player_SwordRunState.h"
#include "Player_Attack3State.h"
#include "Player_SlowRunState.h"
#include "Player_StandState.h"
#include "Player_Jump1State.h"
#include "TimeManager.h"
#include "Sound.h"
#include "GameOver.h"

void Player_DeathState::OnStart()
{
	moveSpeed = m_pPlayer->GetParams().DamageKnockBackSpeed;
	TimeManager::GetInstance().SetTimeScale(0.7f);
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Death), false);
	SoundManager::GetInstance().Play_Sound("SE_Player_Damage");
}

void Player_DeathState::OnUpdate()
{
	frameCount++;
	// ノックバック速度を設定
	moveSpeed -= frameCount * DECEL;
	moveSpeed = std::clamp(moveSpeed, 0.0f, m_pPlayer->GetParams().DamageKnockBackSpeed);

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
		GameOver::GetInstance().StartGameOver();
	}
}

void Player_DeathState::OnExit()
{
	m_pPlayer->SetDamageFlag(false);
	TimeManager::GetInstance().SetTimeScale(1.0f);
}