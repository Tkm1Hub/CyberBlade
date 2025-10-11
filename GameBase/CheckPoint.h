#pragma once
#include "GameObject.h"
class Player;
class CheckPoint :public IGameObject
{
public:
	CheckPoint(const std::string name) : IGameObject(name){}

	void Init() override;

	void SetOwner(std::shared_ptr<Player> player) { owner = player; }

	const float GetHitRadius() const override { return radius; }
	const float GetHitHeight() const override { return height; }

private:
	std::shared_ptr<Player>owner;

	bool isPassed = false;

	VECTOR initPos = { 0.0f,0.0f,50.0f };

	float radius = 20.0f;
	float height = 5.0f;
	
};