#pragma once
#include "EnemyBigStateBase.h"

class EnemyBig_DamageState :public EnemyBigStateBase
{
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	VECTOR m_moveVec = { 0.0f,0.0f,0.0f };
	float m_moveSpeed = 0.0f;
	int m_frameCount = 0;
};