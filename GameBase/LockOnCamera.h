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
	static constexpr float CameraDist = 40.0f;
	static constexpr float CameraHeight = 30.0f;

	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<EnemyBase> lockOnTarget = nullptr;

	VECTOR CulcTargetPos();
	VECTOR CulcCameraPos();

};