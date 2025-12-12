#include "stdafx.h"
#include "EnemyBig_AlertState.h"
#include "EnemyBig_WarningState.h"
#include "EnemyBig.h"
#include "EffectManager.h"
#include "CameraManager.h"

void EnemyBig_AlertState::OnStart()
{
	// アニメ再生
	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::CastPose), false);

	// 警戒フラグ
	m_pEnemyBig->SetIsAlert(true);

}

void EnemyBig_AlertState::OnUpdate()
{
	// 目標角度更新
	m_pEnemyBig->SetTargetAngle(m_pEnemyBig->GetToPlayerDirection());

	// エフェクト再生
	float currentAnimCount = m_pEnemyBig->animation.GetCurrentAnimCount();
	if (currentAnimCount == EFFECT_START_COUNT)
	{
		EffectManager::GetInstance().PlayEffect("Boss_Roar", m_pEnemyBig->GetPosition());
		// カメラの揺れ
		CameraManager::GetCameraManager().GetMainCamera()->StartShake(2.5f, 2.5f, 120.0f);
	}

	// モーションが終わるとWarningに戻す
	if (m_pEnemyBig->animation.GetIsAnimFinished())
	{
		auto spWarningState = std::make_shared<EnemyBig_WarningState>();
		m_pEnemyBig->ChangeState(spWarningState);
		return;
	}

}

void EnemyBig_AlertState::OnExit()
{

}

