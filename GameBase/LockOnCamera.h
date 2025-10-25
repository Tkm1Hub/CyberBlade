#pragma once
#include "VirtualCameraBase.h"
class Player;
class LockOnCamera :public VirtualCameraBase
{
public:
	LockOnCamera(const std::string):VirtualCameraBase(name) {}

	void SetPlayer(const std::weak_ptr<Player>& playerPtr);

	void Init();
	void Update() override;

private:
	std::weak_ptr<Player> player;
};