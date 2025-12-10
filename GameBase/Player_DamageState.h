#pragma once
#include "PlayerStateBase.h"

class Player_DamageState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	bool isInputDodge = false;
	bool isInputJump = false;
	float moveSpeed = 0.0f;
	float timeScale = 0.0f;
	static constexpr float DECEL = 0.005f;
	static constexpr float ACCEL = 0.002f;
};