#pragma once
#include "EnemyBigStateBase.h"

class EnemyBig_AlertState : public EnemyBigStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;
private:
	static constexpr int EFFECT_START_COUNT = 28;
};