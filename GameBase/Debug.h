#pragma once

class IGameObject;
class Debug
{
public:
	void SetObjects(std::vector<std::shared_ptr<IGameObject>> objects)
	{
		owner = objects;
	}

	void Update();
	void Draw();

private:
	std::vector<std::shared_ptr<IGameObject>>owner;

	void DrawCapsule(const std::shared_ptr<IGameObject>& character);
	void DrawCylinder(VECTOR pos, float radius, float height, float division, unsigned int color);
	bool prevF1 = false;
	bool isDebugMode = false;
};