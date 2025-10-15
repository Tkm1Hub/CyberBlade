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
	std::shared_ptr<EnemyManager> m_pEnemyMgr = nullptr;

	// �G�Ɠ��̓����蔻��
	void CheckSwordEnemyCollision();
	// �J�v�Z�����m�̓����蔻��
	bool CheckCapsuleCollision(const std::shared_ptr<IGameObject> obj1, const std::shared_ptr<IGameObject> obj2);
	//�J�v�Z�����m�̋��������߂�
	float DistanceSegmentToSegment(VECTOR p1, VECTOR q1, VECTOR p2, VECTOR q2);

	// �G���m�b�N�o�b�N��������x�N�g�����擾
	VECTOR CulcKnockBackDirection(const std::shared_ptr<EnemyBase>& enemy);
};