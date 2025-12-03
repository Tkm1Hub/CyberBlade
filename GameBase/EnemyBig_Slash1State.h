#pragma once
#include "EnemyBigStateBase.h"
class EnemyBig_Slash1State : public EnemyBigStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	int ATTACK_ACTIVE_COUNT = 33;	// 攻撃を有効化するアニメカウント
	int ATTACK_DISABLE_COUNT = 50;	// 攻撃を無効化するアニメカウント
	int ATTACK_NEXT_COUNT = 48;		// 次の攻撃に移行するアニメカウント
	float ATTACK_SPEED_DECEL = 0.01f;	// 移動速度の減速度

	void AttackMove();
};