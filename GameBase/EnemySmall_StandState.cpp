#include "stdafx.h"
#include "EnemySmall_StandState.h"
#include "EnemySmallDamageState.h"
#include "EnemySmall.h"

void EnemySmall_StandState::OnStart()
{
	// 移動ベクトルの初期化
	m_pEnemySmall->SetMoveVec(VGet(0.0f, 0.0f, 0.0f));

}

void EnemySmall_StandState::OnUpdate()
{
	bool damageFlag = m_pEnemySmall->GetDamageFlag();
	// ダメージを食らったらステート変更
	if (damageFlag)
	{
		auto spDamageState = std::make_shared<EnemySmall_DamageState>();
		m_pEnemySmall->ChangeState(spDamageState);
	}
}

void EnemySmall_StandState::OnExit()
{

}