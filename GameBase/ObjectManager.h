#pragma once
#include "GameObject.h"

class MainCamera;
class SkyDome;
class Stage;
class Player;
class EnemyManager;
class EnemySmall;
class FreeCamera;
class Sword;
class CheckPoint;
class EnemyBase;
class ObjectManager
{
public:
	void Create();
	void AddObject(std::shared_ptr<IGameObject> obj);
	std::shared_ptr<IGameObject> FindObject(std::string name);
	void InitAll();
	void LoadAll();
	void UpdateAll();
	void ApplyCollision();
	void DrawAll();

	const std::vector<std::shared_ptr<IGameObject>>& GetObjects() const { return objects; }
	const std::vector<std::shared_ptr<EnemyBase>>& GetEnemies()const;

private:
	std::vector<std::shared_ptr<IGameObject>> objects;

	std::shared_ptr<SkyDome> skyDome = nullptr;
	std::shared_ptr<Stage> stage = nullptr;
	std::shared_ptr<Player> player = nullptr;
	std::shared_ptr<EnemySmall> enemySmall = nullptr;
	std::shared_ptr<Sword> sword = nullptr;
	std::shared_ptr<CheckPoint> checkPoint = nullptr;
	std::shared_ptr<EnemyManager> enemyMgr = nullptr;
};