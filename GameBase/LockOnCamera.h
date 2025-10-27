#pragma once
#include "VirtualCameraBase.h"
class Player;
class EnemyBase;
class LockOnCamera :public VirtualCameraBase
{
public:
	LockOnCamera(const std::string):VirtualCameraBase(name) {}

	void SetPlayer(const std::shared_ptr<Player>& playerPtr);

	void Init();
	void Update() override;

private:
	static constexpr float CameraDist = 100.0f;
	static constexpr float CameraHeight = 70.0f;

	std::shared_ptr<Player> m_pPlayer;

	VECTOR CulcTargetPos();
	VECTOR CulcCameraPos();

};