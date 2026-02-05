#include "stdafx.h"
#include "EnemyBig_ChaseState.h"
#include "EnemyBig_StandState.h"
#include "EnemyBig_AttackState.h"
#include "EnemyBig.h"
#include "Sound.h"

void EnemyBig_ChaseState::OnStart()
{
	// 移動速度を設定
	m_pEnemyBig->SetMoveSpeed(m_pEnemyBig->GetParams().ChaseSpeed);
	// アニメ再生
	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::Chase), true);

	SoundManager::GetInstance().Play_Sound("SE_Enemy_Walk");
	SoundManager::GetInstance().Play_Sound("SE_Enemy_Move");
}

void EnemyBig_ChaseState::OnUpdate()
{
	// 移動ベクトルをプレイヤーの方向に設定
	VECTOR dir = m_pEnemyBig->GetToPlayerDirection();
	m_pEnemyBig->SetMoveVec(dir);
	m_pEnemyBig->SetTargetAngle(dir);

	// プレイヤーが一定範囲内に入ったら攻撃
	if (m_pEnemyBig->IsPlayerInRange(m_pEnemyBig->GetParams().AttackTriggerRadius))
	{
		auto spAttackState = std::make_shared<EnemyBig_AttackState>();
		m_pEnemyBig->ChangeState(spAttackState);
		return;
	}
}

void EnemyBig_ChaseState::OnExit()
{
	SoundManager::GetInstance().StopSound("SE_Enemy_Walk");
}