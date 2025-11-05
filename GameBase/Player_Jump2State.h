#pragma once
#include "PlayerStateBase.h"
class Player_Jump2State : public PlayerStateBase
{
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};