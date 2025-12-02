#include "stdafx.h"
#include "EnemyBig_WarningState.h"
#include "EnemyBig.h"

void EnemyBig_WarningState::OnStart()
{
	// 移動ベクトルの初期化
	m_pEnemyBig->SetMoveVec(VGet(0.0f, 0.0f, 0.0f));

	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::Warning), true);

	// 警戒フラグ
	m_pEnemyBig->SetIsAlert(true);
}

void EnemyBig_WarningState::OnUpdate()
{

}

void EnemyBig_WarningState::OnExit()
{

}