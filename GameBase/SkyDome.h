#pragma once
#include "GameObject.h"
class Player;
class SkyDome : public IGameObject
{
public:
	SkyDome(const std::string&name):IGameObject(name){}

	void Init() override;
	void Load() override;
	void Update() override;
	void Draw() override;

	void SetOwner(std::shared_ptr<Player> player) { owner = player; }

private:
	VECTOR scale = VGet(1.0f, 1.0f, 1.0f);
	std::shared_ptr<Player> owner = nullptr;
};