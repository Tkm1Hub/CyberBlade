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
	auto player = m_pPlayer.lock();
	// プレイヤーがnullptrの場合早期リターン
	if (!player)
	{
		return;
	}

	if (player->GetIsLockOn())
	{
		lockOnTarget = player->GetLockOnTarget();
		// ロックオン対象が死亡している場合はカメラ切り替えをして早期リターン
		if (lockOnTarget->GetIsDead())
		{
			CameraManager::GetCameraManager().ChangeCamera(0);
			player->SetIsLockOn(false);	// ロックオンフラグをFalseに変更
			return;
		}

		// 注視点とカメラ位置の更新
		target = CulcTargetPos();
		pos = CulcCameraPos();
	}

}

// 注視点を計算
VECTOR LockOnCamera::CulcTargetPos()
{
	auto player = m_pPlayer.lock();
	// プレイヤーがnullptrの場合早期リターン
	if (!player)
	{
		return VGet(0.0f, 0.0f, 0.0f);
	}

	// プレイヤーと敵の座標を取得
	VECTOR playerPos = player->GetTopPos();
	VECTOR enemyPos = lockOnTarget->GetTopPos();

	// 中点の座標
	VECTOR midPos = VScale(VAdd(playerPos, enemyPos), 0.5f);

	return midPos;
}

// カメラの座標を計算
VECTOR LockOnCamera::CulcCameraPos()
{
	auto player = m_pPlayer.lock();
	// プレイヤーがnullptrの場合早期リターン
	if (!player)
	{
		return VGet(0.0f, 0.0f, 0.0f);
	}
	// プレイヤーと敵の座標を取得
	VECTOR playerPos = player->GetTopPos();
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