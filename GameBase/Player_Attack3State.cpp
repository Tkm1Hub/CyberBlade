#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_Attack3State.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"

void Player_Attack3State::OnStart()
{
	m_pPlayer->SetAttackFrag(true);

	// �U���Q�A�j�����Đ�
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Attack3));

	moveSpeed = m_pPlayer->GetParams().Attack2MoveSpeed;

}

void Player_Attack3State::OnUpdate()
{
	m_frameCount++;

	// �����Ă���������ړ��x�N�g���Ƃ��ĕۑ�
	VECTOR moveVec = m_pPlayer->GetTargetMoveDirection();
	m_pPlayer->SetMoveVec(moveVec);
	// �U�����̈ړ����x��t�^
	if(moveSpeed>0.0f) moveSpeed -= 0.02f;
	moveSpeed = max(moveSpeed, 0.0f);
	m_pPlayer->SetMoveSpeed(moveSpeed);

	// �P�S�t���[���ōU���I��
	if (m_frameCount >= 50)
	{
		if (Input::GetInput().GetIsMoveLStick())
		{
			auto spWalkState = std::make_shared<Player_WalkState>();
			m_pPlayer->ChangeState(spWalkState);	// �X�e�B�b�N���͂�����Ε����ɖ߂�
			return;
		}
		else
		{
			auto spStandState = std::make_shared<Player_StandState>();
			m_pPlayer->ChangeState(spStandState);	// �X�e�B�b�N���͂��Ȃ���Η����~�܂�ɖ߂�
			return;
		}
	}
}

void Player_Attack3State::OnExit()
{
	m_pPlayer->SetAttackFrag(false);
}