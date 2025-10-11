#include "stdafx.h"
#include "FreeCamera.h"
#include "Input.h"
#include "Player.h"

void FreeCamera::SetPlayer(const std::weak_ptr<Player>& playerPtr)
{
	player = playerPtr;
}

void FreeCamera::Init()
{
	name = "FreeCamera";
}

void FreeCamera::Update()
{
	if (auto p = player.lock())
	{
		VECTOR playerPos = p->GetPosition();

	// カメラの旋回速度を計算
	currentAngleSpeed = CalcAngleSpeed();

	CalcCameraAngle();

	//カメラの注視点はプレイヤー座標から規定値分高い座標
	target = VAdd(playerPos, VGet(0.0f, LOOK_OFFSET_Y, 0.0f));

	// カメラの座標を補正する
	FixCameraPosition();

	printf("freeCameraPos[%.2f,%.2f,%.2f]\n", pos.x, pos.y, pos.z);
	}
}

void FreeCamera::CalcCameraAngle()
{
	// X軸
	if (0.0f > Input::GetInput().GetRightStickX())
	{
		angleH -= currentAngleSpeed;
		// １８０度以上になったら角度値が大きくなりすぎないように３６０度を足す
		if (angleH > DX_PI_F)
		{
			angleH += DX_TWO_PI_F;
		}
	}
	else if (Input::GetInput().GetRightStickX() > 0.0f)
	{
		angleH += currentAngleSpeed;
		// －１８０度以下になったら角度値が大きくなりすぎないように３６０度を引く
		if (angleH < -DX_PI_F)
		{
			angleH -= DX_TWO_PI_F;
		}
	}

	// Y軸
	if (0.0f > Input::GetInput().GetRightStickY())
	{
		angleV += currentAngleSpeed;
		// ある一定角度以下にはならないようにする
		if (angleV > DX_PI_F * 0.5f - 0.6f)
		{
			angleV = DX_PI_F * 0.5f - 0.6f;
		}
	}
	else if (Input::GetInput().GetRightStickY() > 0.0f)
	{
		angleV -= currentAngleSpeed;
		// ある一定角度以上にはならないようにする
		if (angleV < -DX_PI_F * 0.5f + 0.6f)
		{
			angleV = -DX_PI_F * 0.5f + 0.6f;
		}
	}
}

float FreeCamera::CalcAngleSpeed()
{
	float stickAngle = Input::GetInput().GetRStickAngle();
	float stickPower = abs(stickAngle) / 1000.0f;

	// 傾きに応じた最大速度を計算
	float maxSpeed = MAX_ANGLE_SPEED * stickPower;

	// 加速 or 減速
	if (Input::GetInput().GetIsMoveRStick())
	{
		currentAngleSpeed += ACCEL; // 加速量
		currentAngleSpeed = min(currentAngleSpeed, maxSpeed); // maxSpeedで制限
	}
	else
	{
		currentAngleSpeed -= DECEL; // 減速は固定
		currentAngleSpeed = max(currentAngleSpeed, 0.0f); // マイナスにならないように
	}

	// フラグ
	isMoveAngle = (currentAngleSpeed > 0.0f);

	return currentAngleSpeed;
}

void FreeCamera::FixCameraPosition()
{
	// 水平方向の回転はＹ軸回転
	auto rotY = MGetRotY(angleH);

	// 垂直方向の回転はＺ軸回転 )
	auto rotZ = MGetRotZ(angleV);

	// カメラからプレイヤーまでの初期距離をセット
	float cameraPlayerLength = DISTANCE_OFFSET;

	// カメラの座標を算出
	// Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
	// 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )して更に
	// 注視点の座標を足したものがカメラの座標
	pos = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ), rotY), target);

}
