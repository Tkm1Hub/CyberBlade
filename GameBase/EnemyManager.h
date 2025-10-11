#pragma once

class Character;
class EnemyManager
{
public:
	void AddEnemy(const VECTOR& pos);

	void Init();
	void Load();
	void Update();
	void Draw();

private:
	static constexpr int ENEMY_NUM = 10;
	std::vector<std::shared_ptr<Character>> enemys;
};