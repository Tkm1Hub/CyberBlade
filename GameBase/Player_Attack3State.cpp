#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_Attack3State.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"
#include "Player_DodgeState.h"
#include "Player_JumpState.h"


void Player_Attack3State::OnStart()
{
	m_pPlayer->SetAttackFrag(true);

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

	// １４フレームで攻撃終了
	if (frameCount >= 70)
	{
		if (Input::GetInput().GetIsMoveLStick())
		{
			auto spWalkState = std::make_shared<Player_WalkState>();
			m_pPlayer->ChangeState(spWalkState);	// スティック入力があれば歩きに戻す
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
		auto spJumpState = std::make_shared<Player_JumpState>();
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
}