#pragma once
#include "GameObject.h"

class MainCamera :public IGameObject
{
public:
	MainCamera(const std::string& name) : IGameObject(name){}

	void Init() override;
	void Update() override;

	void SetCameraPositionAndTarget(const VECTOR& newPos, const VECTOR& newTarget);

	const VECTOR GetForward() const { return forward; }

private:
	// 定数
	static constexpr float CAMERA_NEAR = 0.1f;
	static constexpr float CAMERA_FAR = 1300.0f;
	static constexpr float SMOOTHING = 0.1f;			// カメラのスムージング

	// 変数
	VECTOR currentTarget = VGet(0.0f, 0.0f, 0.0f);		// カメラ注視点
	VECTOR nextTarget = VGet(0.0f, 0.0f, 0.0f);			// カメラ注視点の目標位置
	VECTOR forward = VGet(0.0f, 0.0f, 0.0f);			// カメラの方向
	VECTOR currentPosition = VGet(0.0f, 0.0f, 0.0f);	// 現在のポジション
	VECTOR nextPosition = VGet(0.0f, 0.0f, 0.0f);		// 目標のポジション
	float angleH = 0.0f;								// 水平角度
	float angleV = 0.0f;								// 垂直視点
	float currentAngleSpeed = 0.0f;						// 現在のアングル変更速度
	bool isMoveAngle = false;							// カメラが移動中かどうか

	void moveSmoothing();	// スムーズ移動
};