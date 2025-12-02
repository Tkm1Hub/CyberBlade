#include "stdafx.h"
#include "Player_DodgeState.h"
#include "Player_DodgeJustState.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"
#include "Player_RunState.h"
#include "Player_SlowRunState.h"
#include "Player_Jump1State.h"
#include "Player_Attack1State.h"
#include "Player_AttackJump1State.h"
#include "Player_FallState.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Input.h"
#include "TimeManager.h"

void Player_DodgeJustState::OnStart()
{
	// 回避方向を計算
	CulcDodgeDirection();

	// 回避中フラグを立てる
	m_pPlayer->SetIsDodge(true);
	m_pPlayer->SetIsDodgeJust(true);

	// ジャンプ力を0に設定
	m_pPlayer->SetJumpPower(0.0f);

	m_pPlayer->ResetDodgeFrameCount();
	m_pPlayer->SetDodgeSpeed(m_pPlayer->GetParams().DodgeStartSpeed);

	m_pPlayer->animation.Play(static_cast<int>(PlayerAnimState::DodgeJust), false);

	TimeManager::GetInstance().SetTimeScale(0.5f);
}

void Player_DodgeJustState::OnUpdate()
{
	frameCount++;

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

	// 回避中回避ボタンが押されたらフラグを立てる
	if (!isInputDodge && Input::GetInput().GetNowFrameNewInput() & PAD_INPUT_6)
	{
		isInputDodge = true;
	}

	// 受付時間内に攻撃入力で回避攻撃発動
	if (frameCount <= m_pPlayer->GetParams().ATTACK_DODGE_INPUT_WINDOW_FRAMES)
	{
		if (isInputAttack)
		{

		}
	}

	// 硬直終了
	if (frameCount >= m_pPlayer->GetParams().DODGE_JUST_RECOVERY_FRAMES)
	{
		TimeManager::GetInstance().SetTimeScale(1.0f);
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
				// 現在の回避速度が走り速度より小さければ小走り状態
				if (m_pPlayer->GetCurrentDodgeSpeed() < m_pPlayer->GetParams().RunSpeed)
				{
					auto spSlowRunState = std::make_shared<Player_SlowRunState>();
					m_pPlayer->ChangeState(spSlowRunState);
					return;
				}
				else
				{
					auto spRunState = std::make_shared<Player_RunState>();
					m_pPlayer->ChangeState(spRunState);
					return;
				}
			}

			// ジャンプボタンが押されていたらジャンプ
			if (isInputJump)
			{
				auto spJumpState = std::make_shared<Player_Jump1State>();
				m_pPlayer->ChangeState(spJumpState);
				return;
			}

			// 地上で攻撃ボタンが押された場合攻撃１に移行
			if (isInputAttack)
			{
				auto spAttack1State = std::make_shared<Player_Attack1State>();
				m_pPlayer->ChangeState(spAttack1State);
				return;
			}

			// 回避中に回避が押されたらもう一度回避
			if (isInputDodge)
			{
				auto spDodgeState = std::make_shared<Player_DodgeState>();
				m_pPlayer->ChangeState(spDodgeState);
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

void Player_DodgeJustState::OnExit()
{
	m_pPlayer->SetIsDodge(false);
	m_pPlayer->SetIsDodgeJust(false);
}

void Player_DodgeJustState::CulcDodgeDirection()
{
	VECTOR StickDir = VGet(0.0f, 0.0f, 0.0f);	// スティックの方向
	VECTOR modelForward = m_pPlayer->GetModelForward();	// モデルの方向

	// ロックオン中
	if (m_pPlayer->GetIsLockOn())
	{
		// スティックが動いてなければロックオン対象の逆方向方向のベクトルを設定			
		auto target = m_pPlayer->GetLockOnTarget();
		VECTOR targetPos = target->GetPosition();
		VECTOR playerPos = m_pPlayer->GetPosition();


		VECTOR dir = VNorm(VSub(targetPos, playerPos));
		m_pPlayer->SetTargetMoveDirection(dir);

		if (!Input::GetInput().GetIsMoveLStick())
		{
			m_pPlayer->SetDodgeDirection(VScale(dir, -1));
		}
		else
		{
			// スティックが操作中なら方向を左右上下のいずれかに分割して
			// ロックオン対象からその方向にベクトルを設定
			StickDir = m_pPlayer->GetMoveInput();
			StickDir.y = 0.0f;
			StickDir = VNorm(StickDir);

			// 角度
			float angle = atan2(StickDir.x, StickDir.z) - atan2(dir.x, dir.z);

			// -PI ～ PI に収める
			if (angle < -DX_PI_F) angle += DX_TWO_PI_F;
			else if (angle > DX_PI_F) angle -= DX_TWO_PI_F;

			// 角度を 4分割
			if (angle >= -DX_PI_F / 4 && angle <= DX_PI_F / 4) {
				// 正面
				m_pPlayer->SetDodgeDirection(dir);
			}
			else if (angle > DX_PI_F / 4 && angle <= 3 * DX_PI_F / 4) {
				// 右
				m_pPlayer->SetDodgeDirection(RotateY(dir, -DX_PI_F / 2));
			}
			else if (angle < -DX_PI_F / 4 && angle >= -3 * DX_PI_F / 4) {
				// 左
				m_pPlayer->SetDodgeDirection(RotateY(dir, DX_PI_F / 2));
			}
			else {
				// 後ろ
				m_pPlayer->SetDodgeDirection(VScale(dir, -1));
			}

		}

	}
	else
	{
		// 左スティックが入力中なら左スティックのベクトルを返す
		if (Input::GetInput().GetIsMoveLStick())
		{
			StickDir = m_pPlayer->GetMoveInput();
			StickDir.y = 0.0f;
			StickDir = VNorm(StickDir);
			m_pPlayer->SetDodgeDirection(StickDir);
		}
		else
		{
			// スティックが操作されていなければモデルの逆方向に方向を設定
			m_pPlayer->SetDodgeDirection(VScale(modelForward, -1));
		}

	}



}