#pragma once
#include "PlayerStateBase.h"

class Player_DodgeJustState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
private:
	bool isInputJump = false;
	bool isInputDodge = false;

	float moveSpeed = 0.0f;
	float timeScale = 0.0f;

	static constexpr float TIMESCALE_ACCEL = 0.002f;
	static constexpr int DODGE_DISABLE_COUNT = 23;
	static constexpr int SLOW_START_COUNT = 5;

	void CulcDodgeDirection();

	VECTOR RotateY(const VECTOR& dir, float rad)
	{
		VECTOR result;
		result.x = dir.x * cosf(rad) - dir.z * sinf(rad);
		result.y = 0.0f;
		result.z = dir.x * sinf(rad) + dir.z * cosf(rad);
		return result;
	}

};