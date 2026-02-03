#pragma once
class Character;

class BulletFire
{
public:
	BulletFire(const std::shared_ptr<Character>& characterPtr);

	void Init();
	void Update();

	// 全方向に弾を発射
	void FireAllDirection(const VECTOR& pos, int bulletNum, float angleHOffset, float angleVOffset);

	// 水平方向に回転する弾幕を発射
	void FireHorizontalBarrage(const VECTOR& firePos);

	// ウェーブ状の弾幕を発射
	void FireWaveBarrage(const VECTOR& firePos);

	// 弾幕を発射中かのフラグをセット
	void SetIsActiveHorizontalBarrage(bool isActive) { isActiveHorizontalBarrage = isActive; }	// （水平）
	void SetIsActiveWaveBarrage(bool isActive) { isActiveWaveBarrage = isActive; }		// （ウェーブ状）

	float GetBarrageAngleV() { return barrageFireAngleV; }
private:
	// 定数
	// 一度に発車する弾の数
	static constexpr int BULLET_NUM = 6;
	// 全方向に弾を発射する際、一度に発射する弾の数
	static constexpr int BULLET_FIRE_ALL_DIRECTION_NUM = 6;
	// 一度の弾幕で繰り返す発射回数
	static constexpr int BARRAGE_FIRE_LOOP_NUM = 30;
	static constexpr int WAVE_BARRAGE_FIRE_LOOP_NUM = 60;
	// 弾幕発射ごとにずらす角度（水平方向）
	static constexpr float BARRAGE_ANGLE_H_OFFSET = 0.15f;
	static constexpr float WAVE_BARRAGE_ANGLE_H_OFFSET = 0.15f;
	// 弾幕発射ごとにずらす角度（垂直方向）
	static constexpr float BARRAGE_ANGLE_V_OFFSET = 0.01;
	// 波の弾幕での上向きの角度上限
	static constexpr float WAVE_MAX_ANGLE_V = 0.7f;
	// 弾幕が波打つ速さ
	static constexpr float WAVE_SPEED = 0.03f;

	// 変数
	int barrageFireLoopCount = 0;		// 弾幕ループ回数のカウント
	int barrageFrameCount = 0.0f;		// 弾幕を発射するフレームのカウント

	bool isActiveHorizontalBarrage = false;		// 弾幕発射中か（水平）
	bool isActiveWaveBarrage = false;			// 弾幕発射中か（ウェーブ）

	float barrageFireAngleH = 0.0f;		// 弾幕発射角度の基準値（水平）
	float barrageFireAngleV = 0.0f;		// 弾幕発射角度の基準値（垂直）
	float fireAngleH = 0.0f;			// 発射角度（水平）
	float fireAngleV = 0.0f;			// 発射角度（垂直）
	float barrageFireAngleVOffset = 0.05f;		// 

	VECTOR RotateFireHorizontal(const VECTOR& dir, float angleH);	// 水平方向に回転
	VECTOR RotateFireVertical(const VECTOR& dir, float angleV);	// 垂直方向に回転
	std::shared_ptr<Character> character = nullptr;
};