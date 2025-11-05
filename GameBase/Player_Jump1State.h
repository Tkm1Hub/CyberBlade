#pragma once
#include "PlayerStateBase.h"
class Player_Jump1State : public PlayerStateBase
{
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	bool isInputJump = false;
};