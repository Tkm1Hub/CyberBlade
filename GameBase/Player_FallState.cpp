#include "stdafx.h"
#include "Input.h"
#include "Player.h"
#include "Player_FallState.h"

void Player_FallState::OnStart()
{
	// 落下アニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Fall));
}

void Player_FallState::OnUpdate()
{

	// 重力を適応
	float currentJumpPower = m_pPlayer->GetCurrentJumpPower();
	currentJumpPower -= m_pPlayer->GetParams().Gravity;
	m_pPlayer->SetJumpPower(currentJumpPower);
}

void Player_FallState::OnExit()
{

}