#pragma once
#include "EnemySmallStateBase.h"

class EnemySmall_AttackState : public EnemySmallStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
private:
	VECTOR attackDir = { 0.0f,0.0f,0.0f };
};