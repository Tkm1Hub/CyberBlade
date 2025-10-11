#include "stdafx.h"
#include "EnemySmall_StandState.h"
#include "EnemySmallDamageState.h"
#include "EnemySmall.h"

void EnemySmall_StandState::OnStart()
{
	// �ړ��x�N�g���̏�����
	m_pEnemySmall->SetMoveVec(VGet(0.0f, 0.0f, 0.0f));

}

void EnemySmall_StandState::OnUpdate()
{
	// �_���[�W��H�������X�e�[�g�ύX
	if (m_pEnemySmall->GetDamageFlag())
	{
		auto spDamageState = std::make_shared<EnemySmall_DamageState>();
		m_pEnemySmall->ChangeState(spDamageState);
	}
}

void EnemySmall_StandState::OnExit()
{

}