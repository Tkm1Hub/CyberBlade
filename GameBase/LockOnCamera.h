#pragma once
#include "VirtualCameraBase.h"
class Player;
class EnemyBase;
class LockOnCamera :public VirtualCameraBase
{
public:
	LockOnCamera(const std::string):VirtualCameraBase(name) {}

	void SetPlayer(const std::shared_ptr<Player>& playerPtr) { m_pPlayer = playerPtr; }

	void Init();
	void Update() override;

private:
	// 定数
	static constexpr float DISTANCE_OFFSET = 30.0f;	// プレイヤーからの距離
	static constexpr float HEIGHT_OFFSET = 8.0f;	// カメラの高さ

	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<EnemyBase> lockOnTarget = nullptr;

	VECTOR CulcTargetPos();
	VECTOR CulcCameraPos();

};