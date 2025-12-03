#include "stdafx.h"
#include "EnemyBig_WarningState.h"
#include "EnemyBig_AttackState.h"
#include "EnemyBig_Slash1State.h"
#include "EnemyBig.h"

void EnemyBig_WarningState::OnStart()
{
	// ÉAÉjÉÅçƒê∂
	m_pEnemyBig->animation.Play(static_cast<int>(EnemyBigAnimState::Warning), true);

	// åxâ˙ÉtÉâÉO
	m_pEnemyBig->SetIsAlert(true);
}

void EnemyBig_WarningState::OnUpdate()
{
	// ñ⁄ïWäpìxçXêV
	m_pEnemyBig->SetTargetAngle(m_pEnemyBig->GetToPlayerDirection());

	// çUåÇîÕàÕÇ…ì¸Ç¡ÇΩÇÁãﬂãóó£çsìÆ
	if (m_pEnemyBig->IsPlayerInRange(m_pEnemyBig->GetParams().AttackTriggerRadius))
	{
		int random = GetRand(1);

		switch (random)
		{
		case 0:		// çUåÇ
		{
			auto spAttackState = std::make_shared<EnemyBig_AttackState>();
			m_pEnemyBig->ChangeState(spAttackState);
			break;
		}
		case 1:		// ì„Ç¨ï•Ç¢ÇP
		{
			auto spSlash1State = std::make_shared<EnemyBig_Slash1State>();
			m_pEnemyBig->ChangeState(spSlash1State);
			break;
		}

		}
	}


}

void EnemyBig_WarningState::OnExit()
{
	
}

