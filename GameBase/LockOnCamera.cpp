#include "stdafx.h"
#include "LockOnCamera.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EnemyBase.h"

void LockOnCamera::Init()
{

}

void LockOnCamera::Update()
{
	if (!m_pPlayer)
	{
		printf("LockOnCamera: Player is nullptr!\n");
		return;
	}

	if (m_pPlayer->GetIsLockOn())
	{
		target = CulcTargetPos();
		pos = CulcCameraPos();
	}

	printf("LockOnCamera Pos:(%.2f, %.2f, %.2f) Target:(%.2f, %.2f, %.2f)\n",
		pos.x, pos.y, pos.z, target.x, target.y, target.z);
}

// 注視点を計算
VECTOR LockOnCamera::CulcTargetPos()
{
	// プレイヤーと敵の座標を取得
	VECTOR playerPos = m_pPlayer->GetPosition();
	lockOnTarget = m_pPlayer->GetLockOnTarget();
	VECTOR enemyPos = lockOnTarget->GetPosition();

	// 中点の座標
	VECTOR midPos = VScale(VAdd(playerPos, enemyPos), 0.5f);
	midPos.y += CameraHeight;

	return midPos;
}

// カメラの座標を計算
VECTOR LockOnCamera::CulcCameraPos()
{
	// プレイヤーと敵の座標を取得
	VECTOR playerPos = m_pPlayer->GetPosition();
	lockOnTarget = m_pPlayer->GetLockOnTarget();
	VECTOR enemyPos = lockOnTarget->GetPosition();

	// 敵とプレイヤーの距離を計算
	VECTOR diff = VSub(playerPos, enemyPos);
	diff.y = 0.0f;

	// 敵からプレイヤーへの方向ベクトル
	VECTOR dir = VNorm(diff);

	// カメラの座標（playerPos + dir * dist）
	VECTOR CameraPos = VGet(playerPos.x, playerPos.y + CameraHeight, playerPos.z);
	CameraPos = VAdd(CameraPos, VScale(dir, CameraDist));

	return CameraPos;
}