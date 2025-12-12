#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_Attack3State.h"
#include "Player_SwordRunState.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"
#include "Player_DodgeState.h"
#include "Player_Jump1State.h"
#include "Player_DamageState.h"


void Player_Attack3State::OnStart()
{
	// 装備フラグ
	m_pPlayer->SetIsSwordEquipped(true);
	m_pPlayer->SetAttackFrag(true);
	m_pPlayer->SetIsAttackEnabled(true);

	// 攻撃２アニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Attack3),false);

	moveSpeed = m_pPlayer->GetParams().Attack2MoveSpeed;

}

void Player_Attack3State::OnUpdate()
{
	frameCount++;

	// 向いている方向を移動ベクトルとして保存
	VECTOR moveVec = m_pPlayer->GetAttackDir();
	m_pPlayer->SetTargetMoveDirection(moveVec);
	// 攻撃中の移動速度を付与
	if(moveSpeed>0.0f) moveSpeed -= 0.02f;
	moveSpeed = max(moveSpeed, 0.0f);
	m_pPlayer->SetMoveSpeed(moveSpeed);

	// ダメージを食らったら状態変更
	if (m_pPlayer->GetDamageFlag())
	{
		auto spDamageState = std::make_shared<Player_DamageState>();
		m_pPlayer->ChangeState(spDamageState);
		return;
	}


	// １４フレームで攻撃終了
	if (frameCount >= 70)
	{
		if (Input::GetInput().GetIsMoveLStick())
		{
			auto spSwordRunState = std::make_shared<Player_SwordRunState>();
			m_pPlayer->ChangeState(spSwordRunState);	// スティック入力があれば小走り（装備）に戻す
			return;
		}
		else
		{
			auto spStandState = std::make_shared<Player_StandState>();
			m_pPlayer->ChangeState(spStandState);	// スティック入力がなければ立ち止まりに戻す
			return;
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

void Player_Attack3State::OnExit()
{
	m_pPlayer->SetAttackFrag(false);
	m_pPlayer->SetIsSwordEquipped(false);
	m_pPlayer->SetIsAttackEnabled(false);
}