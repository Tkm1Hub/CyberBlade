#pragma once
#include "Character.h"
#include "StateMachine.h"

class EnemySmallStateBase;
class EnemyBase :public Character
{
public:
	EnemyBase(const std::string& name) :Character(name) {}

	void Draw() override;

	void SetDamageFlag(bool flag) { isDamage = flag; }
	const bool GetDamageFlag() const { return isDamage; }


	VECTOR GetKnockBackDir()const { return knockBackDir; }
	void SetKnockBackDir(const VECTOR& direction) { knockBackDir = direction; }

	int GetHitPoint()const { return hp; }
	int SetHitPoint(int newHp){ hp = newHp; }
	void ApplyDamage(int damage) { hp -= damage; }

	const bool GetIsDead()const { return isDead; }
	void Kill() { isDead = true; }

protected:
	void Move();				// 移動処理

	StateMachine stateMachine;	// ステートマシン

	VECTOR knockBackDir = { 0.0f,0.0f,0.0f };

	bool isDamage = false;
	bool isDead = false;

	int hp = 0;

};