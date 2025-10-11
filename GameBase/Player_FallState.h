#pragma once
#include "PlayerStateBase.h"
class Player_FallState :public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};