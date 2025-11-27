#pragma once
#include "EnemyBigStateBase.h"
class EnemyBig_FallState :public EnemyBigStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};