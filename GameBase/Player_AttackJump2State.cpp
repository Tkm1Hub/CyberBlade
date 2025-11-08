#include "stdafx.h"
#include "Player_AttackJump1State.h"
#include "Player_AttackJump2State.h"
#include "Player_FallState.h"
#include "Player_DodgeState.h"
#include "Player.h"
#include "Input.h"

void Player_AttackJump2State::OnStart()
{
	// 攻撃フラグ
	m_pPlayer->SetAttackFrag(true);
	// 装備フラグ
	m_pPlayer->SetIsSwordEquipped(true);

	// アニメ再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::AttackJump2), false);

	// 移動速度を設定
	frontMoveSpeed = m_pPlayer->GetParams().AttackJump1MoveSpeed;

	// ジャンプ力を0に設定
	m_pPlayer->SetJumpPower(0.0f);

}

void Player_AttackJump2State::OnUpdate()
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

	if (frameCount >= 15)
	{
		if (isInputAttack)
		{
			// 空中攻撃1に移行する
			auto spAttackJump1State = std::make_shared<Player_AttackJump1State>();
			m_pPlayer->ChangeState(spAttackJump1State);
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

void Player_AttackJump2State::OnExit()
{
	m_pPlayer->SetAttackFrag(false);
	m_pPlayer->SetIsSwordEquipped(false);

}