#pragma once
#include "PlayerStateBase.h"

class Player_StandState : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
private:
	int frameCount = 0;
	bool isAttackReady = false;
};