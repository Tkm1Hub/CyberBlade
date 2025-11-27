#pragma once
#include "EnemyBigStateBase.h"

class EnemyBig_StandState : public EnemyBigStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
};