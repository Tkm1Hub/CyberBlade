#include "stdafx.h"
#include "EnemyBig_WarningState.h"
#include "EnemyBig_AttackState.h"
#include "EnemyBig_Slash1State.h"
#include "EnemyBig_DodgeState.h"
#include "EnemyBig_FallState.h"
#include "EnemyBig.h"

void EnemyBig_WarningState::OnStart()
{
	// ƒAƒjƒÄ¶
	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::Warning), true);

	// Œx‰úƒtƒ‰ƒO
	m_pEnemyBig->SetIsAlert(true);
}

void EnemyBig_WarningState::OnUpdate()
{
	// –Ú•WŠp“xXV
	m_pEnemyBig->SetTargetAngle(m_pEnemyBig->GetToPlayerDirection());

	// UŒ‚”ÍˆÍ‚É“ü‚Á‚½‚ç‹ß‹——£s“®
	if (m_pEnemyBig->IsPlayerInRange(m_pEnemyBig->GetParams().AttackTriggerRadius))
	{
		int random = GetRand(2);

		switch (random)
		{
		case 0:		// UŒ‚
		{
			auto spAttackState = std::make_shared<EnemyBig_AttackState>();
			m_pEnemyBig->ChangeState(spAttackState);
			break;
		}
		case 1:		// “ã‚¬•¥‚¢‚P
		{
			auto spSlash1State = std::make_shared<EnemyBig_Slash1State>();
			m_pEnemyBig->ChangeState(spSlash1State);
			break;
		}
		case 2:		// ‰ñ”ğ
		{
			auto spDodgeState = std::make_shared<EnemyBig_DodgeState>();
			m_pEnemyBig->ChangeState(spDodgeState);
			break;
		}

		}

		//// ‹ó’†‚É‚¢‚ê‚Î—‰º
		//if (m_pEnemyBig->GetIsJumping())
		//{
		//	auto spFallState = std::make_shared<EnemyBig_FallState>();
		//	m_pEnemyBig->ChangeState(spFallState);
		//	return;
		//}
	}


}

void EnemyBig_WarningState::OnExit()
{
	
}

