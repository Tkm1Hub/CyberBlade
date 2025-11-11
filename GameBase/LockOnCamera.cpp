#include "stdafx.h"
#include "LockOnCamera.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "CameraManager.h"

void LockOnCamera::Init()
{

}

void LockOnCamera::Update()
{
	// プレイヤーがnullptrの場合早期リターン
	if (!m_pPlayer)
	{
		printf("LockOnCamera: Player is nullptr!\n");
		return;
	}

	if (m_pPlayer->GetIsLockOn())
	{
		lockOnTarget = m_pPlayer->GetLockOnTarget();
		// ロックオン対象が死亡している場合はカメラ切り替えをして早期リターン
		if (lockOnTarget->GetIsDead())
		{
			CameraManager::GetCameraManager().ChangeCamera(0);
			m_pPlayer->SetIsLockOn(false);	// ロックオンフラグをFalseに変更
			return;
		}

		// 注視点とカメラ位置の更新
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
	VECTOR playerPos = m_pPlayer->GetTopPos();
	VECTOR enemyPos = lockOnTarget->GetTopPos();

	// 中点の座標
	VECTOR midPos = VScale(VAdd(playerPos, enemyPos), 0.5f);

	return midPos;
}

// カメラの座標を計算
VECTOR LockOnCamera::CulcCameraPos()
{
	// プレイヤーと敵の座標を取得
	VECTOR playerPos = m_pPlayer->GetTopPos();
	VECTOR enemyPos = lockOnTarget->GetTopPos();

	// 敵とプレイヤーの距離を計算
	VECTOR diff = VSub(playerPos, enemyPos);
	diff.y = 0.0f;

	// 敵からプレイヤーへの方向ベクトル
	VECTOR dir = VNorm(diff);

	angleH = static_cast<float>(atan2(dir.z, -dir.x));

	// カメラの座標（playerPos + dir * dist）
	VECTOR CameraPos = VGet(playerPos.x, playerPos.y + HEIGHT_OFFSET, playerPos.z);
	CameraPos = VAdd(CameraPos, VScale(dir, DISTANCE_OFFSET));

	return CameraPos;
}