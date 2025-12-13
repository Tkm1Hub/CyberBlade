#pragma once
#include "PlayerStateBase.h"
class Player_Attack1State :public PlayerStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	float moveSpeed = 0.0f;
	bool m_doNextAttack = false;
	static constexpr int ATTACK_ENABLE_COUNT = 6;
	static constexpr int ATTACK_DISABLE_COUNT = 12;
};