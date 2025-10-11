#pragma once
#include "EnemySmallStateBase.h"

class EnemySmall_DamageState :public EnemySmallStateBase
{
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	VECTOR m_moveVec = { 0.0f,0.0f,0.0f };
	float m_moveSpeed = 0.0f;
	int m_frameCount = 0;
};