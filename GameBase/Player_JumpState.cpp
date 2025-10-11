#include "stdafx.h"
#include "Input.h"
#include "Player.h"
#include "Player_FallState.h"
#include "Player_JumpState.h"

void Player_JumpState::OnStart()
{
	// �W�����v�͂����Z
	m_pPlayer->SetJumpPower(m_pPlayer->GetParams().JumpPower);
	
	// �W�����v�t���O���X�V
	m_pPlayer->SetIsJumping(true);

	// �W�����v�A�j�����Đ�
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Jump));

}

void Player_JumpState::OnUpdate()
{

	// �d�͂�K��
	float currentJumpPower = m_pPlayer->GetCurrentJumpPower();
	currentJumpPower -= m_pPlayer->GetParams().Gravity;
	m_pPlayer->SetJumpPower(currentJumpPower);

	// �W�����v�͂��O�ȉ����Ɨ�����
	if (m_pPlayer->GetCurrentJumpPower() < 0.0f)
	{
		auto spFallState = std::make_shared<Player_FallState>();
		m_pPlayer->ChangeState(spFallState);
	}
}

void Player_JumpState::OnExit()
{

}