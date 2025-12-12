#include "stdafx.h"
#include "MainCamera.h"
#include "TimeManager.h"

void MainCamera::Init()
{
	pos = VGet(0.0f, 50.0f, -30.0f);
	currentTarget = VGet(0.0f, 30.0f, 0.1f);
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
	isMoveSmoothing = true;
}

void MainCamera::Update()
{
	// スムーズに移動
	if (isMoveSmoothing)
	{
		moveSmoothing();
	}

	// カメラの揺れ
	Shake();

	VECTOR finalPos = VAdd(pos, shakeOffset);
	VECTOR finalTarget = VAdd(currentTarget, shakeOffset);

	// カメラの方向を保存
	forward = VSub(finalPos, finalTarget);
	forward.y = 0.0f;
	forward = VNorm(forward);

	// 位置と注視点の設定
	SetCameraPositionAndTarget_UpVecY(finalPos, finalTarget);
}

// カメラの座標とターゲットを設定
void MainCamera::SetCameraPositionAndTarget(const VECTOR& newPos, const VECTOR& newTarget)
{
	nextPosition = newPos;
	nextTarget = newTarget;
}

/// <summary>
/// スムーズに移動
/// </summary>
void MainCamera::moveSmoothing()
{
	// 目標地点と現在位置の差を取得
	VECTOR diff = VSub(nextPosition, pos);
	VECTOR targetDiff = VSub(nextTarget, currentTarget);

	// 差にスムージングをかける
	diff = VScale(diff, SMOOTHING);
	targetDiff = VScale(targetDiff, SMOOTHING);

	// 現在位置に加算
	pos = VAdd(pos, diff);
	currentTarget = VAdd(currentTarget, targetDiff);
}

// カメラ揺れを開始
void MainCamera::StartShake(float powerX,float powerY, float duration)
{
	shakePowerX = powerX;
	shakePowerY = powerY;
	shakeTime = duration;
	shakeDuration = duration;
}

void MainCamera::Shake()
{
	float dt = TimeManager::GetInstance().GetTimeScale();

	// 揺れの計算
	if (shakeTime > 0.0f)
	{
		shakeTime -= dt;
		shakeTime = max(0.0f, shakeTime);

		float t = shakeTime / shakeDuration;

		float currentShakeX = shakePowerX * t; // 横揺れ
		float currentShakeY = shakePowerY * t; // 縦揺れ

		shakeTimer -= dt;
		if (shakeTimer <= 0.0f)
		{
			shakeTimer += SHAKE_INTARVAL; // 次の更新までの残り時間をセット

			// ランダム生成は更新間隔でのみ発生
			float randX = ((rand() % 2001) - 1000) / 1000.0f;
			float randY = ((rand() % 2001) - 1000) / 1000.0f;

			shakeOffsetX = randX * currentShakeX;
			shakeOffsetY = randY * currentShakeY;
		}
	}
	else
	{
		shakeOffsetX = 0.0f;
		shakeOffsetY = 0.0f;
	}

	// 横と縦を計算
	VECTOR forward = VSub(pos, currentTarget);
	forward = VNorm(forward);

	VECTOR up = VGet(0.0f, 1.0f, 0.0f);

	VECTOR right = VCross(up, forward);
	right = VNorm(right);

	VECTOR realUp = VCross(forward, right);
	realUp = VNorm(realUp);

	// 揺れオフセット作成
	shakeOffset =
		VAdd(
			VScale(right, shakeOffsetX),      // 横揺れ
			VScale(realUp, shakeOffsetY)      // 縦揺れ
		);
}