#pragma once
#include "GameObject.h"

class Stage :public IGameObject
{
public:
	Stage(const std::string& name) : IGameObject(name){}

	void Init() override;
	void Load() override;
	void Draw() override;

	const int GetModelHandle() const { return modelHandle; }
	const int GetCollisionModelHandle() const { return collisionModelHandle; }

private:
	int collisionModelHandle = -1;
};