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
};