#include "stdafx.h"
#include "Player_AttackJump1State.h"
#include "Player_AttackJump2State.h"
#include "Player_FallState.h"
#include "Player_DodgeState.h"
#include "Player.h"
#include "Input.h"
#include "Player_DamageState.h"

void Player_AttackJump1State::OnStart()
{
	// 攻撃フラグ
	m_pPlayer->SetAttackFrag(true);
	m_pPlayer->SetIsAttackEnabled(true);

	// 装備フラグ
	m_pPlayer->SetIsSwordEquipped(true);

	// アニメ再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Attack1), false);

	// 移動速度を設定
	frontMoveSpeed = m_pPlayer->GetParams().AttackJump1MoveSpeed;

	// ジャンプ力を0に設定
	m_pPlayer->SetJumpPower(0.0f);
}

void Player_AttackJump1State::OnUpdate()
{
	frameCount++;

	// 攻撃の方向ベクトルを適用
	VECTOR moveVec = m_pPlayer->GetAttackDir();
	m_pPlayer->SetTargetMoveDirection(moveVec);

	// 移動速度を減速
	if (frontMoveSpeed > 0.0f) frontMoveSpeed -= 0.1f;
	frontMoveSpeed = max(frontMoveSpeed, 0.0f);
	m_pPlayer->SetMoveSpeed(frontMoveSpeed);

	// 攻撃ボタンが押されたらフラグ
	if (!isInputAttack && Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_1)
	{
		isInputAttack = true;
	}

	// ダメージを食らったら状態変更
	if (m_pPlayer->GetDamageFlag())
	{
		auto spDamageState = std::make_shared<Player_DamageState>();
		m_pPlayer->ChangeState(spDamageState);
		return;
	}


	if (frameCount >= 15)
	{
		if (isInputAttack)
		{
			// 空中攻撃2に移行する
			auto spAttackJump2State = std::make_shared<Player_AttackJump2State>();
			m_pPlayer->ChangeState(spAttackJump2State);
			return;
		}
	}

	// 落下開始
	if (frameCount >= 30)
	{
		// 攻撃フラグ解除
		m_pPlayer->SetAttackFrag(false);

		// 落下状態に移行する
		auto spFallState = std::make_shared<Player_FallState>();
		m_pPlayer->ChangeState(spFallState);
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

void Player_AttackJump1State::OnExit()
{
	m_pPlayer->SetAttackFrag(false);
	m_pPlayer->SetIsSwordEquipped(false);
	m_pPlayer->SetIsAttackEnabled(false);
}