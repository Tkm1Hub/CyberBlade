#pragma once
#include "EnemyBigStateBase.h"

class EnemyBig_JumpAttackState : public EnemyBigStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	const int JUMP_START_COUNT = 10;	//ジャンプを開始するアニメカウント
	const int JUMP_END_COUNT = 42;	// 着地するするアニメカウント

	VECTOR targetPos = { 0.0f,0.0f,0.0f };	// 着地地点の座標
	float prevJumpHeight = 0.0f;

	void AttackMove();
};