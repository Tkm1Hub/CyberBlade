#include "stdafx.h"
#include "MainCamera.h"

void MainCamera::Init()
{
	pos = VGet(0.0f, 50.0f, -30.0f);
	currentTarget = VGet(0.0f, 30.0f, 0.1f);
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
}

void MainCamera::Update()
{
	moveSmoothing();

	// カメラの方向を保存
	forward = VSub(pos, currentTarget);
	forward.y = 0.0f;
	forward = VNorm(forward);

	// 位置と注視点の設定
	SetCameraPositionAndTarget_UpVecY(pos, currentTarget);
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