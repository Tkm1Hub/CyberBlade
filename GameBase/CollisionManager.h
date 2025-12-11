#pragma once
#include "ObjectManager.h"

class IGameObject;
class StageCollision;
class Player;
class EnemySmall;
class Sword;
class Stage;
class EnemyBase;
class CollisionManager
{
public:
	void SetObjects(std::vector<std::shared_ptr<IGameObject>>objectsPtr)
	{
		objects = objectsPtr;
	}

	void SetEnemies(std::vector<std::shared_ptr<EnemyBase>> enemies)
	{
		m_pEnemies = enemies;
	}

	void Init();

	void Update();

private:
	std::vector<std::shared_ptr<IGameObject>>objects;
	std::vector<std::shared_ptr<EnemyBase>> m_pEnemies;
	std::shared_ptr<StageCollision> stageCollision = nullptr;
	std::shared_ptr<Player> m_pPlayer = nullptr;
	std::shared_ptr<EnemySmall> m_pEnemySmall = nullptr;
	std::shared_ptr<Sword> m_pSword = nullptr;
	std::shared_ptr<Stage> m_pStage = nullptr;

	// 敵と刀の当たり判定
	void CheckSwordEnemyCollision();

	// 敵の手とプレイヤーの当たり判定
	void CheckEnemyAttackPlayerCollision();

	// カプセル同士の当たり判定
	bool CheckCapsuleCollision(const std::shared_ptr<IGameObject> obj1, const std::shared_ptr<IGameObject> obj2);
	// カプセルと球の当たり判定
	bool CheckCapsuleSphereCollision(const VECTOR& capTop, const VECTOR& capBottom, const float capRadius, const VECTOR& spherePos, float sphereRadius);

	//カプセル同士の距離を求める
	float DistanceSegmentToSegment(VECTOR p1, VECTOR q1, VECTOR p2, VECTOR q2);

	// 敵がノックバックする方向ベクトルを取得
	VECTOR CulcKnockBackDirection(const std::shared_ptr<IGameObject>& attackObj, const std::shared_ptr<IGameObject>& damageObj);

	// カプセル同士の衝突を判定して押し戻し
	bool ResolveCapsuleCollision(std::shared_ptr<IGameObject> objA, std::shared_ptr<IGameObject> objB);

	VECTOR ClosestPointOnSegment(const VECTOR& a, const VECTOR& b, const VECTOR& p);
};