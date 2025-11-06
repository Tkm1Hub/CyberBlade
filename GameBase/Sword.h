#pragma once
#include "GameObject.h"
class Player;
class Sword :public IGameObject
{
public:
	Sword(const std::string name) :IGameObject(name){}

	void Init()override;
	void Load() override;
	void Update() override;
	void Draw() override;

	void SetOwner(std::shared_ptr<Player> player) { owner = player; }

	const float GetHitRadius() const override { return HitRadius; }
	const float GetHitHeight() const override { return HitHeight; }

	const VECTOR GetTopPos() override;
	const VECTOR GetBottomPos() override;

private:
	// “‚Ìƒ{[ƒ“”Ô† 
	int bladeStartIndex = -1;
	int bladeEndIndex = -1;

	VECTOR offsetPos = { 0.0f,0.0f,0.0f };
	VECTOR offsetRot = { 0.0f,0.0f,0.0f };
	std::shared_ptr<Player> owner = nullptr;

	// “–‚½‚è”»’è
	float HitRadius = 1.5f;
	float HitHeight = 10.0f;

};