#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_AttackDashState.h"
#include "Player_Attack3State.h"
#include "Player_RunState.h"
#include "Player_StandState.h"

void Player_AttackDashState::OnStart()
{
	m_pPlayer->SetAttackFrag(true);

	// �A�j�����Đ�
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::AttackDash));

	moveSpeed = m_pPlayer->GetParams().AttackDashMoveSpeed;

}

void Player_AttackDashState::OnUpdate()
{
	m_frameCount++;

	if (!m_doNextAttack)
	{
		if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_1)
		{
			m_doNextAttack = true;
		}
	}


	if (m_frameCount >= 20)
	{
		if (m_doNextAttack)
		{
			auto spAttack3State = std::make_shared<Player_Attack3State>();
			m_pPlayer->ChangeState(spAttack3State);
		}

		if (m_frameCount >= 30)
		{
			if (Input::GetInput().GetIsMoveLStick())
			{
				auto spWalkState = std::make_shared<Player_RunState>();
				m_pPlayer->ChangeState(spWalkState);	// �X�e�B�b�N���͂�����Α���ɖ߂�
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
}

void Player_AttackDashState::OnExit()
{
	m_pPlayer->SetAttackFrag(false);
}