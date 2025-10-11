#pragma once
#include "PlayerStateBase.h"
class Player_Attack3State :public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	int m_frameCount = 0;
	float moveSpeed = 0.0f;
};