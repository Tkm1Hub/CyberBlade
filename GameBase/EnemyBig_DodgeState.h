#pragma once
#include "EnemyBigStateBase.h"

class EnemyBig_DodgeState : public EnemyBigStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	const int DODGE_ACTIVE_COUNT = 8;	// 回避を開始するアニメカウント
	const int DODGE_DISABLE_COUNT = 23;	// 回避を終了するアニメカウント
	const float DODGE_SPEED_DECEL = 0.01;	// 回避の減速度

	float dodgeSpeed = 0.0f;			// 回避中移動速度

	VECTOR targetDir = { 0.0f,0.0f,0.0f };	// 目標の角度
	VECTOR dodgeDir = { 0.0f,0.0f,0.0f };	// 回避する方向

	void DodgeMove();
	VECTOR CulcDodgeDir(VECTOR& DirToPlayer);
};