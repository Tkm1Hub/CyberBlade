#pragma once
#include "PlayerStateBase.h"

class Player_AttackJump2State : public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
private:
	float frontMoveSpeed = 0.0f;	// ‘O•ûˆÚ“®‘¬“x
};