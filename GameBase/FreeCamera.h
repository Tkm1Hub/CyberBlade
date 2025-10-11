#pragma once
#include "VirtualCameraBase.h"

class Player;
class FreeCamera : public VirtualCameraBase
{
public:
	FreeCamera(const std::string& name): VirtualCameraBase(name){}

	void SetPlayer(const std::weak_ptr<Player>& playerPtr);

	void Init();
	void Update() override;

private:

	// 定数
	static constexpr float MAX_ANGLE_SPEED = 0.04f;		// 最大旋回速度
	static constexpr float ANGLESPEED = 0.03f;			// カメラ感度
	static constexpr float ACCEL = 0.01f;				// カメラ加速度
	static constexpr float DECEL = 0.005f;				// カメラ減速度
	static constexpr float LOOK_OFFSET_Y = 20.0f;		// 注視点の高さ
	static constexpr float DISTANCE_OFFSET = 40.0f;		// プレイヤーからの距離

	// 変数
	float currentAngleSpeed = 0.0f;						// 現在のカメラ旋回速度
	float angleH = 0.0f;								// 水平角度
	float angleV = 0.0f;								// 垂直角度
	bool isMoveAngle = false;							// カメラが移動中か

	std::weak_ptr<Player> player;

	void CalcCameraAngle();		// カメラのアングルを計算
	float CalcAngleSpeed();		// カメラの旋回速度を計算
	void FixCameraPosition();	// カメラ座標を補正する
};