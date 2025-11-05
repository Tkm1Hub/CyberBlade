#include "stdafx.h"
#include "Player_DodgeState.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"
#include "Player_RunState.h"
#include "Player_JumpState.h"
#include "Player_Attack1State.h"
#include "Player_AttackJump1State.h"
#include "Player_FallState.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Input.h"

void Player_DodgeState::OnStart()
{
	// 移動ベクトルを後ろ方向に設定
	VECTOR playerDirection = m_pPlayer->GetTargetMoveDirection();
	VECTOR dodgeDirection = VScale(playerDirection, -1);
	m_pPlayer->SetTargetMoveDirection(dodgeDirection);

	// 回避中フラグを立てる
	m_pPlayer->SetIsDodge(true);

	// 回避アニメーションを再生
	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::DodgeBack),false);

	// ジャンプ力を0に設定
	m_pPlayer->SetJumpPower(0.0f);
}

void Player_DodgeState::OnUpdate()
{
	frameCount++;

	// 移動速度を設定
	if (frameCount < m_pPlayer->GetParams().DODGE_BACK_BOOST_WAIT_FRAMES)
	{
		moveSpeed = m_pPlayer->GetParams().DodgeStartSpeed;
	}
	else if(frameCount >= m_pPlayer->GetParams().DODGE_BACK_BOOST_WAIT_FRAMES 
		&& frameCount < m_pPlayer->GetParams().DODGE_RECOVERY_FRAMES)
	{
		moveSpeed = m_pPlayer->GetParams().DodgeSpeed;
	}
	else if (frameCount >= m_pPlayer->GetParams().DODGE_RECOVERY_FRAMES)
	{
		moveSpeed -= 0.1f;
		moveSpeed = max(moveSpeed, 0.0f);
	}

	m_pPlayer->SetMoveSpeed(moveSpeed);

	// 回避中攻撃ボタンが押されたらフラグを立てる
	if (!isInputAttack && Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_1)
	{
		isInputAttack = true;
	}

	// 回避中ジャンプボタンが押されたらフラグを立てる
	if (!isInputJump && Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_3)
	{
		isInputJump = true;
	}

	// 受付時間内に攻撃入力で回避攻撃発動
	if (frameCount <= m_pPlayer->GetParams().ATTACK_DODGE_INPUT_WINDOW_FRAMES)
	{
		if (isInputAttack)
		{

		}
	}

	// 硬直終了
	if (frameCount >= m_pPlayer->GetParams().DODGE_RECOVERY_FRAMES)
	{
		// 空中にいるかどうか
		if (m_pPlayer->GetIsJumping())
		{
			// スティック入力があれば即座に落下に移行
			if (Input::GetInput().GetIsMoveLStick())
			{
				// 落下に移行
				auto spFallState = std::make_shared<Player_FallState>();
				m_pPlayer->ChangeState(spFallState);
				return;
			}

			// 回避中、空中にいる状態で攻撃ボタンが押された場合、空中攻撃１に移行
			if (isInputAttack)
			{
				auto spAttackJump1State = std::make_shared<Player_AttackJump1State>();
				m_pPlayer->ChangeState(spAttackJump1State);
				return;
			}
			else
			{
				// 落下に移行
				auto spFallState = std::make_shared<Player_FallState>();
				m_pPlayer->ChangeState(spFallState);
				return;
			}
		}
		else
		{
			// スティック入力があれば走り状態に変更
			if (Input::GetInput().GetIsMoveLStick())
			{
				auto spRunState = std::make_shared<Player_RunState>();
				m_pPlayer->ChangeState(spRunState);
				return;
			}

			// 地上で攻撃ボタンが押された場合攻撃１に移行
			if (isInputAttack)
			{
				auto spAttack1State = std::make_shared<Player_Attack1State>();
				m_pPlayer->ChangeState(spAttack1State);
				return;
			}
		}


		// アニメ終了
		if (m_pPlayer->animation.GetIsAnimFinished())
		{
			// スティック入力がなければStandに戻す
			if (!Input::GetInput().GetIsMoveLStick())
			{
				auto spStandState = std::make_shared<Player_StandState>();
				m_pPlayer->ChangeState(spStandState);
				return;
			}
		}
	}
}

void Player_DodgeState::OnExit()
{
	m_pPlayer->SetIsDodge(false);

	m_pPlayer->SetKeepForwardAfterDodge(true);

	//VECTOR playerDirection = m_pPlayer->GetTargetMoveDirection();
	//VECTOR dodgeDirection = VScale(playerDirection, -1);
	//m_pPlayer->SetTargetMoveDirection(dodgeDirection);
}

void Player_DodgeState::CulcDodgeDirection()
{
	VECTOR StickDir = VGet(0.0f, 0.0f, 0.0f);	// スティックの方向
	VECTOR modelForward = m_pPlayer->GetModelForward();	// モデルの方向

	// 左スティックが入力中なら左スティックのベクトルを返す
	if (Input::GetInput().GetIsMoveLStick())
	{
		StickDir = m_pPlayer->GetMoveInput();
		StickDir.y = 0.0f;
		StickDir = VNorm(StickDir);
		m_pPlayer->SetDodgeDirection(StickDir);
	}

	// ロックオン中
	if (m_pPlayer->GetIsLockOn())
	{
		if (!Input::GetInput().GetIsMoveLStick())
		{
			// スティックが動いてなければロックオン対象の逆方向方向のベクトルを設定
			auto target = m_pPlayer->GetLockOnTarget();
			VECTOR targetPos = target->GetPosition();
			VECTOR playerPos = m_pPlayer->GetPosition();

			VECTOR dir = VNorm(VScale(VSub(playerPos, targetPos), -1));
			m_pPlayer->SetDodgeDirection(dir);
		}
		else
		{
			
		}

	}
	else
	{

	}
	


	// 角度
	float angle = atan2(StickDir.x, StickDir.z) - atan2(modelForward.x, modelForward.z);

	// -PI ～ PI に収める
	if (angle < -DX_PI_F) angle += DX_TWO_PI_F;
	else if (angle > DX_PI_F) angle -= DX_TWO_PI_F;

	// 角度を 4分割
	if (angle >= -DX_PI_F / 4 && angle <= DX_PI_F / 4) {
		// 正面
		return StickDir;
	}
	else if (angle > DX_PI_F / 4 && angle <= 3 * DX_PI_F / 4) {
		// 右
		return StickDir;
	}
	else if (angle < -DX_PI_F / 4 && angle >= -3 * DX_PI_F / 4) {
		// 左
		return StickDir;
	}
	else {
		// 後ろ
		
	}
}