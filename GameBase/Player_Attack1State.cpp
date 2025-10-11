#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_Attack1State.h"
#include "Player_Attack2State.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"

void Player_Attack1State::OnStart()
{
	m_pPlayer->SetAttackFrag(true);

	// 攻撃１アニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Attack1));

	moveSpeed = m_pPlayer->GetParams().Attack1MoveSpeed;

}

void Player_Attack1State::OnUpdate()
{
	m_frameCount++;

	// 向いている方向を移動ベクトルとして保存
	VECTOR moveVec = m_pPlayer->GetTargetMoveDirection();
	m_pPlayer->SetMoveVec(moveVec);

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

	// ２４フレームで攻撃終了
	if (m_frameCount >= 20)
	{
		if (m_doNextAttack)
		{
			auto spAttack2State = std::make_shared<Player_Attack2State>();
			m_pPlayer->ChangeState(spAttack2State);	// 次の攻撃に移行
			return;
		}
		else if (Input::GetInput().GetIsMoveLStick())
		{
			auto spWalkState = std::make_shared<Player_WalkState>();
			m_pPlayer->ChangeState(spWalkState);	// スティック入力があれば歩きに戻す
			return;
		}
		else if(!Input::GetInput().GetIsMoveLStick())
		{
			auto spStandState = std::make_shared<Player_StandState>();
			m_pPlayer->ChangeState(spStandState);	// スティック入力がなければ立ち止まりに戻す
			return;
		}
	}
}

void Player_Attack1State::OnExit()
{
	m_pPlayer->SetAttackFrag(false);
}