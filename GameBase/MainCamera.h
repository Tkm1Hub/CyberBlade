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

	void SetIsMoveSmoothing(bool flag) { isMoveSmoothing = flag; }

	void StartShake(float powerX,float powerY, float duration);

private:
	// 定数
	static constexpr float CAMERA_NEAR = 0.1f;
	static constexpr float CAMERA_FAR = 2000.0f;
	static constexpr float SMOOTHING = 0.1f;			// カメラのスムージング
	static constexpr float SHAKE_INTARVAL = 0.02f;		// 揺れ更新の間隔

	// 変数
	VECTOR currentTarget = VGet(0.0f, 0.0f, 0.0f);		// カメラ注視点
	VECTOR nextTarget = VGet(0.0f, 0.0f, 0.0f);			// カメラ注視点の目標位置
	VECTOR forward = VGet(0.0f, 0.0f, 0.0f);			// カメラの方向
	VECTOR currentPosition = VGet(0.0f, 0.0f, 0.0f);	// 現在のポジション
	VECTOR nextPosition = VGet(0.0f, 0.0f, 0.0f);		// 目標のポジション
	VECTOR shakeOffset = VGet(0.0f, 0.0f, 0.0f);		// 揺れのオフセット
	VECTOR shakeoffsetTarget = VGet(0.0f, 0.0f, 0.0f);	// カメラ揺れの目標地点
	float angleH = 0.0f;								// 水平角度
	float angleV = 0.0f;								// 垂直視点
	float currentAngleSpeed = 0.0f;						// 現在のアングル変更速度
	float shakePowerX = 0.0f;							// 横揺れの強さ
	float shakePowerY = 0.0f;							// 縦揺れの強さ
	float shakeOffsetX = 0.0f;							// 横揺れのオフセット
	float shakeOffsetY = 0.0f;							// 縦揺れのオフセット
	float shakeTime = 0.0f;								// 揺れる残り時間
	float shakeDuration = 0.0f;							// 揺れる総時間
	float shakeTimer = 0.0f;							// 揺れ更新の間隔
	bool isMoveAngle = false;							// カメラが移動中かどうか
	bool isMoveSmoothing = false;						// スムージングを利用するか

	void moveSmoothing();	// スムーズ移動
	void Shake();			// カメラ揺れ
};