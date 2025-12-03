#pragma once
#include "EnemyBigStateBase.h"

class EnemyBig_WarningState : public EnemyBigStateBase
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnExit() override;

private:
	const int SelectRandomAction();

	// ƒXƒe[ƒg”Ô†
	enum class State : int
	{
		Attack = 0,			// UŒ‚‚P
		Slash1 = 1,			// “ã‚¬•¥‚¢‚P
		Slash2 = 2,			// “ã‚¬•¥‚¢‚Q
		AttackJump = 3,		// ƒWƒƒƒ“ƒvUŒ‚
		Dodge = 4,			// ‰ñ”ğ
		Jump = 5,			// ƒWƒƒƒ“ƒviÕŒ‚”gj
		Cast1 = 6,			// ’e–‹‚P
		Cast2 = 7,			// ’e–‹‚Q
		Fire = 8,			// ‰“‹——£UŒ‚
	};
};