#include "stdafx.h"
#include "LockOnCamera.h"
#include "Player.h"
#include "EnemyManager.h"

void LockOnCamera::Update()
{
	target = CulcTargetPos();
}

// 注視点を計算
VECTOR LockOnCamera::CulcTargetPos()
{
	// プレイヤーと敵の座標を取得
	VECTOR playerPos = m_pPlayer->GetPosition();
	VECTOR enemyPos = EnemyManager::GetEnemyManager().GetNearestEnemyPos(playerPos);

	// 中点の座標
	VECTOR midPos = VScale(VAdd(playerPos, enemyPos), 0.5f);

	return midPos;
}

// カメラの座標を計算
VECTOR LockOnCamera::CulcCameraPos()
{
	// プレイヤーと敵の座標を取得
	VECTOR playerPos = m_pPlayer->GetPosition();
	VECTOR enemyPos = EnemyManager::GetEnemyManager().GetNearestEnemyPos(playerPos);

	// 敵とプレイヤーの距離を計算
	VECTOR diff = VSub(playerPos, enemyPos);

	// 敵からプレイヤーへの方向ベクトル
	VECTOR dir = VNorm(diff);

	// カメラの座標（playerPos + dir * dist）
	VECTOR CameraPos = VAdd(playerPos, VScale(dir, CameraDist));

	return CameraPos;
}