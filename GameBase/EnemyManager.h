#pragma once

class EnemyBase;
class EnemyManager
{
public:
	void AddEnemy(std::shared_ptr<EnemyBase> enemy,const VECTOR& initPos);

	void Init();
	void Load();
	void Update();
	void Draw();
	void ApplyCollision();
	void RemoveDeadEnemies();

	const std::vector<std::shared_ptr<EnemyBase>>& GetEnemies() const { return enemies; }

private:
	static constexpr int ENEMY_NUM = 10;
	std::vector<std::shared_ptr<EnemyBase>> enemies;
};