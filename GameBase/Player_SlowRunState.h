#pragma once
#include "PlayerStateBase.h"

class Player_SlowRunState :public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};