#pragma once
#include "EnemySmallStateBase.h"

class EnemySmall_ChaseState : public EnemySmallStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};