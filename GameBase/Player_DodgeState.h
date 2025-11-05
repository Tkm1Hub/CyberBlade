#pragma once
#include "PlayerStateBase.h"

class Player_DodgeState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
private:
	bool isInputJump = false;

	float moveSpeed = 0.0f;

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