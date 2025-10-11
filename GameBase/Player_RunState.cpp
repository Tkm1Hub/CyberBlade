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
	// �����Ԃ̃t���O�𗧂Ă�
	m_pPlayer->SetRunFlag(true);

	m_pPlayer->SetMoveFlag(true);

	// ���x�ύX
	float currentMoveSpeed = m_pPlayer->GetParams().RunSpeed;
	m_pPlayer->SetMoveSpeed(currentMoveSpeed);

	// �����A�j�����Đ�
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Run));
}

void Player_RunState::OnUpdate()
{

	// �X�e�B�b�N���͂��Ȃ��ꍇStand�ɖ߂�
	if (!Input::GetInput().GetIsMoveLStick())
	{
		auto spStandState = std::make_shared<Player_StandState>();
		m_pPlayer->ChangeState(spStandState);
		return;
	}

	// A�i�R�j�{�^���ŃW�����v
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
	{
		auto spJumpState = std::make_shared<Player_JumpState>();
		m_pPlayer->ChangeState(spJumpState);
		return;
	}

	// X�i�P�j�{�^���Ń_�b�V���U��
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