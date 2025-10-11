#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_Attack2State.h"
#include "Player_Attack3State.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"

void Player_Attack2State::OnStart()
{
	m_pPlayer->SetAttackFrag(true);

	// �U���Q�A�j�����Đ�
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Attack2));

	moveSpeed = m_pPlayer->GetParams().Attack2MoveSpeed;
}

void Player_Attack2State::OnUpdate()
{
	m_frameCount++;

	// �����Ă���������ړ��x�N�g���Ƃ��ĕۑ�
	VECTOR moveVec = m_pPlayer->GetTargetMoveDirection();
	m_pPlayer->SetMoveVec(moveVec);
	// �U�����̈ړ����x��t�^
	if (moveSpeed > 0.0f) moveSpeed -= 0.02f;
	moveSpeed = max(moveSpeed, 0.0f);
	m_pPlayer->SetMoveSpeed(moveSpeed);

	if (!m_doNextAttack)
	{
		if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_1)
		{
			m_doNextAttack = true;
		}
	}

	// �P�S�t���[���ōU���I��
	if (m_frameCount >= 18)
	{
		if (m_doNextAttack)
		{
			auto spAttack3State = std::make_shared<Player_Attack3State>();
			m_pPlayer->ChangeState(spAttack3State);	// ���̍U���Ɉڍs
		}
		else if (Input::GetInput().GetIsMoveLStick())
		{
			auto spWalkState = std::make_shared<Player_WalkState>();
			m_pPlayer->ChangeState(spWalkState);	// �X�e�B�b�N���͂�����Ε����ɖ߂�
			return;
		}
		else if (!Input::GetInput().GetIsMoveLStick())
		{
			auto spStandState = std::make_shared<Player_StandState>();
			m_pPlayer->ChangeState(spStandState);	// �X�e�B�b�N���͂��Ȃ���Η����~�܂�ɖ߂�
			return;
		}
	}
}

void Player_Attack2State::OnExit()
{
	m_pPlayer->SetAttackFrag(false);
}