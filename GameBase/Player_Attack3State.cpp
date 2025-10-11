#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "Player_Attack3State.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"

void Player_Attack3State::OnStart()
{
	m_pPlayer->SetAttackFrag(true);

	// 攻撃２アニメを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::Attack3));

	moveSpeed = m_pPlayer->GetParams().Attack2MoveSpeed;

}

void Player_Attack3State::OnUpdate()
{
	m_frameCount++;

	// 向いている方向を移動ベクトルとして保存
	VECTOR moveVec = m_pPlayer->GetTargetMoveDirection();
	m_pPlayer->SetMoveVec(moveVec);
	// 攻撃中の移動速度を付与
	if(moveSpeed>0.0f) moveSpeed -= 0.02f;
	moveSpeed = max(moveSpeed, 0.0f);
	m_pPlayer->SetMoveSpeed(moveSpeed);

	// １４フレームで攻撃終了
	if (m_frameCount >= 50)
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
}

void Player_Attack3State::OnExit()
{
	m_pPlayer->SetAttackFrag(false);
}