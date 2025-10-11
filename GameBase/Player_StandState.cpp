#include "stdafx.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"
#include "Player_JumpState.h"
#include "Player_Attack1State.h"
#include "Player.h"
#include "Input.h"

void Player_StandState::OnStart()
{
	// �ړ��x�N�g���̏�����
	m_pPlayer->SetMoveVec(VGet(0.0f, 0.0f, 0.0f));

	// �����Ԃ̃t���O������
	m_pPlayer->SetRunFlag(false);
	m_pPlayer->SetMoveFlag(false);

	// �A�C�h���A�j�����Đ�
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Idle));
}

void Player_StandState::OnUpdate()
{
	// ���X�e�B�b�N�����͒��Ȃ�ړ�
	if (Input::GetInput().GetIsMoveLStick())
	{
		auto spWalkState = std::make_shared<Player_WalkState>();
		m_pPlayer->ChangeState(spWalkState);
		return;
	}

	// A�i�R�j�{�^���ŃW�����v
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
	{
		auto spJumpState = std::make_shared<Player_JumpState>();
		m_pPlayer->ChangeState(spJumpState);
		return;
	}

	// X�i�P�j�{�^���ōU��
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