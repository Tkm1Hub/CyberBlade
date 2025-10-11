#pragma once
#include "PlayerStateBase.h"
class Player_JumpState : public PlayerStateBase
{
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};