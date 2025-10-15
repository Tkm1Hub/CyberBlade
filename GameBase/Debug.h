#pragma once

class IGameObject;
class EnemyBase;
class Debug
{
public:
	void SetObjects(std::vector<std::shared_ptr<IGameObject>> objects)
	{
		owner = objects;
	}

	void SetEnemies(std::vector<std::shared_ptr<EnemyBase>> enemies)
	{
		m_enemies = enemies;
	}

	void Update();
	void Draw();

private:
	std::vector<std::shared_ptr<IGameObject>>owner;
	std::vector<std::shared_ptr<EnemyBase>>m_enemies;

	void DrawCapsule(const std::shared_ptr<IGameObject>& character);
	void DrawCylinder(VECTOR pos, float radius, float height, float division, unsigned int color);
	bool prevF1 = false;
	bool isDebugMode = false;
};