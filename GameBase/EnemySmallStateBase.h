#pragma once
#include "StateBase.h"

class EnemySmall;
class EnemySmallStateBase : public StateBase
{
public:
	void SetOwner(EnemySmall* a_pEnemySmall)
	{
		m_pEnemySmall = a_pEnemySmall;
	}

protected:
	EnemySmall* m_pEnemySmall = nullptr;
};