#include "stdafx.h"
#include "CollisionManager.h"
#include "StageCollision.h"
#include "Player.h"
#include "EnemySmall.h"
#include "Sword.h"
#include "Stage.h"


void CollisionManager::Init()
{
	stageCollision = std::make_shared<StageCollision>();

	for (auto obj : objects)
	{
		// �X�e�[�W���f���̃n���h����n��
		if (obj->GetName() == "Stage")
		{
            m_pStage = std::dynamic_pointer_cast<Stage>(obj);

            int modelHandle = m_pStage->GetCollisionModelHandle();
			stageCollision->SetStageCollision(modelHandle);
		}
		// �v���C���[�̃|�C���^��n��
		if (obj->GetName() == "Player")
		{
			m_pPlayer = std::dynamic_pointer_cast<Player>(obj);
		}
		// �G�̃|�C���^��n��
		if (obj->GetName() == "EnemySmall")
		{
			m_pEnemySmall = std::dynamic_pointer_cast<EnemySmall>(obj);
		}
		// ���̃|�C���^��n��
		if (obj->GetName() == "Sword")
		{
			m_pSword = std::dynamic_pointer_cast<Sword>(obj);
		}
	}
}

void CollisionManager::Update()
{
    // �v���C���[���U�����̏ꍇ�A�G�Ɠ��̓����蔻����s��
    if (m_pPlayer->GetIsAttack())
    {
        CheckSwordEnemyCollision();
    }

	for (auto obj : objects)
	{
		if (obj->GetIsStageCollisionEnabled())
		{
			VECTOR nextPos = stageCollision->CheckCollision(*obj, obj->GetNextPosition());
			obj->SetNextPosition(nextPos);
		}
	}
}

// �G�Ɠ��̓����蔻��
void CollisionManager::CheckSwordEnemyCollision()
{
    if (CheckCapsuleCollision(m_pEnemySmall, m_pSword))
    {
        if (!m_pEnemySmall->GetDamageFlag())
        {
            m_pEnemySmall->SetDamageFlag(true);
            VECTOR knockBackDirection = CulcKnockBackDirection();
            m_pEnemySmall->SetKnockBackDir(knockBackDirection);
        }
    }

}

// �J�v�Z�����m�̓����蔻��
bool CollisionManager::CheckCapsuleCollision(const std::shared_ptr<IGameObject> objA, const std::shared_ptr<IGameObject> objB)
{
	float RadiusA = objA->GetHitRadius();    // ���a

	float RadiusB = objB->GetHitRadius();    // ���a
    
    // �J�v�Z���̏㉺�̍��W���擾
    VECTOR TopA = objA->GetCapsuleAPos();
    VECTOR BottomA = objA->GetCapsuleBPos();

    VECTOR TopB = objB->GetCapsuleAPos();
    VECTOR BottomB = objB->GetCapsuleBPos();

	// �J�v�Z���Ԃ̍ŋߐڋ������v�Z�i�������m�j
	float distance = DistanceSegmentToSegment(BottomA, TopA, BottomB, TopB);

	return distance < (RadiusA + RadiusB);		// �J�v�Z�����m�̏Փ˔���
}

// �J�v�Z�����m�̍ŒZ���������߂�
float CollisionManager::DistanceSegmentToSegment(VECTOR p1, VECTOR q1, VECTOR p2, VECTOR q2)
{
    VECTOR d1 = VSub(q1, p1);  // ����1
    VECTOR d2 = VSub(q2, p2);  // ����2
    VECTOR r = VSub(p1, p2);

    float a = VDot(d1, d1);  // ������2��
    float e = VDot(d2, d2);
    float f = VDot(d2, r);

    float s, t;

    if (a <= 0.0001f && e <= 0.0001f)
    {
        return VSize(r); // �����Ƃ��_
    }

    if (a <= 0.0001f)
    {
        s = 0.0f;
        t = f / e;
        t = (t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t));
    }
    else
    {
        float c = VDot(d1, r);
        if (e <= 0.0001f)
        {
            t = 0.0f;
            s = -c / a;
            s = (s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s));
        }
        else
        {
            float b = VDot(d1, d2);
            float denom = a * e - b * b;

            if (denom != 0.0f)
            {
                s = (b * f - c * e) / denom;
                s = (s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s));
            }
            else
            {
                s = 0.0f;
            }

            t = (b * s + f) / e;

            if (t < 0.0f)
            {
                t = 0.0f;
                s = (-c) / a;
                s = (s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s));
            }
            else if (t > 1.0f)
            {
                t = 1.0f;
                s = (b - c) / a;
                s = (s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s));
            }
        }
    }

    VECTOR c1 = VAdd(p1, VScale(d1, s));
    VECTOR c2 = VAdd(p2, VScale(d2, t));

    return VSize(VSub(c1, c2));
}

VECTOR CollisionManager::CulcKnockBackDirection()
{
    VECTOR playerPos = m_pPlayer->GetPosition();
    VECTOR enemyPos = m_pEnemySmall->GetPosition();

    VECTOR directionEnemyToPlayer = VSub(playerPos, enemyPos);
    directionEnemyToPlayer = VNorm(directionEnemyToPlayer);
    
    VECTOR knockBackDirection = VScale(directionEnemyToPlayer, -1.0f);
    return knockBackDirection;
}