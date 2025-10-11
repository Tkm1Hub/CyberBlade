#pragma once
#include "PlayerStateBase.h"

class Player_RunState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};