#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_AttackDashState.h"
#include "Player_SwordRunState.h"
#include "Player_Attack3State.h"
#include "Player_RunState.h"
#include "Player_StandState.h"
#include "Player_DodgeState.h"
#include "Player_Jump1State.h"
#include "Player_DamageState.h"


void Player_AttackDashState::OnStart()
{
	// 装備フラグ
	m_pPlayer->SetIsSwordEquipped(true);
	m_pPlayer->SetAttackFrag(true);

	// アニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::AttackDash),false);

	moveSpeed = m_pPlayer->GetParams().AttackDashMoveSpeed;

}

void Player_AttackDashState::OnUpdate()
{
	frameCount++;
	float currentAnimCount = m_pPlayer->animation.GetCurrentAnimCount();

	if (currentAnimCount >= ATTACK_ENABLE_COUNT && currentAnimCount <= ATTACK_DISABLE_COUNT)
	{
		m_pPlayer->SetIsAttackEnabled(true);
	}
	else if (currentAnimCount >= ATTACK_DISABLE_COUNT)
	{
		m_pPlayer->SetIsAttackEnabled(false);
	}

	if (!m_doNextAttack)
	{
		if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_1)
		{
			m_doNextAttack = true;
		}
	}

	// ダメージを食らったら状態変更
	if (m_pPlayer->GetDamageFlag())
	{
		auto spDamageState = std::make_shared<Player_DamageState>();
		m_pPlayer->ChangeState(spDamageState);
		return;
	}


	if (currentAnimCount >= ATTACK_DISABLE_COUNT)
	{
		if (m_doNextAttack)
		{
			auto spAttack3State = std::make_shared<Player_Attack3State>();
			m_pPlayer->ChangeState(spAttack3State);
			return;
		}

		if (m_pPlayer->animation.GetIsAnimFinished())
		{
			if (Input::GetInput().GetIsMoveLStick())
			{
				auto spSwordRunState = std::make_shared<Player_SwordRunState>();
				m_pPlayer->ChangeState(spSwordRunState);	// スティック入力があれば小走り（装備）に戻す
				return;
			}
			else if (!Input::GetInput().GetIsMoveLStick())
			{
				auto spStandState = std::make_shared<Player_StandState>();
				m_pPlayer->ChangeState(spStandState);	// スティック入力がなければ立ち止まりに戻す
				return;
			}
		}
	}

	// A（３）ボタンでジャンプ
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
	{
		auto spJumpState = std::make_shared<Player_Jump1State>();
		m_pPlayer->ChangeState(spJumpState);
		return;
	}

	// R（8）ボタンで回避
	if (Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_6)
	{
		auto spDodgeState = std::make_shared<Player_DodgeState>();
		m_pPlayer->ChangeState(spDodgeState);
		return;
	}
}

void Player_AttackDashState::OnExit()
{
	m_pPlayer->SetAttackFrag(false);
	m_pPlayer->SetIsSwordEquipped(false);
	m_pPlayer->SetIsAttackEnabled(false);
}