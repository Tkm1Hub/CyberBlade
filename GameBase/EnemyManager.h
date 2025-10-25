#pragma once

class EnemyBase;
class EnemyManager
{
private:
	// コンストラクタを非公開にする
	EnemyManager(){}

	// コピーコンストラクタと代入演算子を削除
	EnemyManager(const EnemyManager&) = delete;
	EnemyManager& operator=(const EnemyManager&) = delete;

	//プライベートデストラクタ
	~EnemyManager() {}
public:

	// インスタンスを取得するためのメソッド
	static EnemyManager& GetEnemyManager()
	{
		static EnemyManager instance;      // 静的変数としてインスタンスを定義
		return instance;
	}

	void AddEnemy(std::shared_ptr<EnemyBase> enemy,const VECTOR& initPos);

	void Init();
	void Load();
	void Update();
	void Draw();
	void ApplyCollision();
	void RemoveDeadEnemies();
	VECTOR GetNearestEnemyPos(const VECTOR& playerPos)const;

	const std::vector<std::shared_ptr<EnemyBase>>& GetEnemies() const { return enemies; }

private:
	static constexpr int ENEMY_NUM = 10;
	std::vector<std::shared_ptr<EnemyBase>> enemies;
};