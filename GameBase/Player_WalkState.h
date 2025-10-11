#pragma once
#include "PlayerStateBase.h"

class Player_WalkState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};