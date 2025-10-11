#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "CameraManager.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"
#include "Player_JumpState.h"
#include "Player_FallState.h"
#include "Player_RunState.h"

void Player::Init()
{
	modelScale = VGet(0.1f, 0.1f, 0.1f);
	isStageCollisionEnabled = true;
	isCollisionEnabled = true;
	isShadowEnabled = true;
	auto spStandState = std::make_shared<Player_StandState>();
	ChangeState(spStandState);
	hitHeight = params.HitHeight;
	hitRadius = params.HitRadius;
}

void Player::Load()
{
	// モデルハンドル取得
	modelHandle = MV1LoadModel("data/model/character/Hideron.mv1");
	handBoneIndex = MV1SearchFrame(modelHandle, "Hand_R.001");
	MV1SetScale(modelHandle, modelScale);
	MV1SetPosition(modelHandle, pos);

	// アニメーションのロード
	animation.LoadAnimation(modelHandle);
	// アイドルを再生
	animation.Play(static_cast<int>(PlayerAnimState::Idle));
}

void Player::Update()
{
	if (!isAttack)
	{
		// スティックでの移動入力
		moveVec = GetMoveInput();
	}

	// ステートの更新
	stateMachine.Update();

	// 次の座標を計算
	Move();

	// モデルの方向更新
	UpdateAngle();

	// アニメーションの更新
	animation.Update();

	handMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, handBoneIndex);
}

void Player::Draw()
{
	MV1DrawModel(modelHandle);
}

void Player::ChangeState(std::shared_ptr<PlayerStateBase> a_spState)
{
	a_spState->SetOwner(this);
	stateMachine.ChangeState(a_spState);
}

void Player::Move()
{
	// HACK: 移動距離が0.01未満で微妙に移動していた場合はじんわり移動してバグる
// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
	if (fabs(moveVec.x) > 0.01f || fabs(moveVec.z) > 0.01f)
	{
		isMove = true;
	}
	else
	{
		isMove = false;
	}

	// 移動速度を計算
	if (!isAttack)
	{
		CulcMoveSpeed();
	}
	moveVec = VScale(targetMoveDirection, currentMoveSpeed);

	// 移動ベクトルのＹ成分をＹ軸方向の速度にする
	moveVec.y = currentJumpPower;

	nextPos = VAdd(pos,moveVec);

	//Y座標が-100以下になったら座標を初期化する
	if (pos.y < -1000.0f || pos.y>500)
	{
		pos = params.InitPos;
		nextPos = params.InitPos;
	}

	printf("targetMoveDirection [ %.2f,%.2f,%.2f ]\n", targetMoveDirection.x, targetMoveDirection.y, targetMoveDirection.z);
	printf("currentMoveSpeed : %f\n", currentMoveSpeed);
}

void Player::CulcMoveSpeed()
{
	if (isMove)
	{
		currentMoveSpeed += params.Accel;
	}
	else
	{
		currentMoveSpeed -= params.decel;
	}

	// 限界値を超えたら修正
	if (isRunning)
	{
		currentMoveSpeed = std::clamp(currentMoveSpeed, 0.0f, params.RunSpeed);
	}
	else
	{
		currentMoveSpeed = std::clamp(currentMoveSpeed, 0.0f, params.WalkSpeed);
	}
}

void Player::UpdateAngle()
{
	// プレイヤーの移動方向にモデルの方向を近づける
	float targetAngle;			// 目標角度
	float difference;			// 目標角度と現在の角度との差
	float speed = params.AngleSpeed;	// 角度変更速度


	// 目標の方向ベクトルから角度値を算出する
	targetAngle = static_cast<float>(atan2(targetMoveDirection.x, targetMoveDirection.z));

	// 目標の角度と現在の角度との差を割り出す
	// 最初は単純に引き算
	difference = targetAngle - angle;

	// ある方向からある方向の差が１８０度以上になることは無いので
	// 差の値が１８０度以上になっていたら修正する
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	// 角度の差が０に近づける
	if (difference > 0.0f)
	{
		// 差がプラスの場合は引く
		difference -= speed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else
	{
		// 差がマイナスの場合は足す
		difference += speed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	// モデルの角度を更新
	angle = targetAngle - difference;

	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// <summary>
/// 天井に当たった時
/// </summary>
void Player::OnHitRoof()
{
	// Ｙ軸方向の速度は反転
	currentJumpPower = -currentJumpPower;
}

/// <summary>
/// 床に当たった時
/// </summary>
void Player::OnHitFloor()
{
	// Ｙ軸方向の移動速度は０に
	currentJumpPower = 0.0f;

	// もしジャンプ中だった場合は着地状態にする
	if (isJumping)
	{
		// 移動していたかどうかで着地後の状態と再生するアニメーションを分岐する
		if (isMove)
		{
			if (isRunning)
			{
				auto spRunState = std::make_shared<Player_RunState>();
				ChangeState(spRunState);
			}
			else
			{
				auto spWalkState = std::make_shared<Player_WalkState>();
				ChangeState(spWalkState);
			}
		}
		else
		{
			auto spStandState = std::make_shared<Player_StandState>();
			ChangeState(spStandState);
		}

		// 着地時はアニメーションのブレンドは行わない
		// animation->SetBlendRate(1.0f);
		isJumping = false;
	}
}

/// <summary>
/// 落下が確定したとき
/// </summary>
void Player::OnFall()
{
	if (!isJumping)
	{
		// ジャンプ中(落下中）にする
		auto spFallState = std::make_shared<Player_FallState>();
		ChangeState(spFallState);
		isJumping = true;

		// ちょっとだけジャンプする
		currentJumpPower = FallUpPower;
	}
}

VECTOR Player::GetMoveInput()
{
	VECTOR mVec = VGet(0.0f, 0.0f, 0.0f);

	// カメラの前方向ベクトルを取得
	VECTOR camForward = CameraManager::GetCameraManager().GetMainCamera()->GetForward();
	VECTOR camRight = VCross(camForward, VGet(0.0f, 1.0f, 0.0f));
	camRight = VNorm(camRight);

	// スティック入力
	float stickX = Input::GetInput().GetLeftStickX();
	float stickY = Input::GetInput().GetLeftStickY();

	// 移動ベクトル
	mVec = VAdd(VScale(camRight, stickX), VScale(camForward, stickY));
	if (VSize(mVec) != 0.0f)
	{
		targetMoveDirection = VNorm(mVec);
	}

	return mVec;
}
