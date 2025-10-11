#pragma once
#include "EnemySmallStateBase.h"
class EnemySmall_FallState:public EnemySmallStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};