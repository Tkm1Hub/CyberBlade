#pragma once
#include "ObjectManager.h"

class IGameObject;
class StageCollision;
class Player;
class EnemySmall;
class Sword;
class Stage;
class CollisionManager
{
public:
	void SetObjects(std::vector<std::shared_ptr<IGameObject>>objectsPtr)
	{
		objects = objectsPtr;
	}

	void Init();

	void Update();

private:
	std::vector<std::shared_ptr<IGameObject>>objects;
	std::shared_ptr<StageCollision> stageCollision = nullptr;
	std::shared_ptr<Player> m_pPlayer = nullptr;
	std::shared_ptr<EnemySmall> m_pEnemySmall = nullptr;
	std::shared_ptr<Sword> m_pSword = nullptr;
	std::shared_ptr<Stage> m_pStage = nullptr;

	// 敵と刀の当たり判定
	void CheckSwordEnemyCollision();
	// カプセル同士の当たり判定
	bool CheckCapsuleCollision(const std::shared_ptr<IGameObject> obj1, const std::shared_ptr<IGameObject> obj2);
	//カプセル同士の距離を求める
	float DistanceSegmentToSegment(VECTOR p1, VECTOR q1, VECTOR p2, VECTOR q2);

	// 敵がノックバックする方向ベクトルを取得
	VECTOR CulcKnockBackDirection();
};