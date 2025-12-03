#pragma once
#include "StateBase.h"

class EnemyBig;
class EnemyBigStateBase : public StateBase
{
public:
	void SetOwner(EnemyBig* a_pEnemyBig)
	{
		m_pEnemyBig = a_pEnemyBig;
	}

protected:
	EnemyBig* m_pEnemyBig = nullptr;
	VECTOR attackDir = { 0.0f,0.0f,0.0f };
	float attackSpeed = 0.0f;

};