#pragma once
#include "Character.h"
#include "StateMachine.h"

class Player;
class EnemyBase :public Character
{
public:
	EnemyBase(const std::string& name) :Character(name) {}

	void Draw() override;

	void SetDamageFlag(bool flag) { isDamage = flag; }
	const bool GetDamageFlag() const { return isDamage; }

	void SetHp(int newHp) { hp = newHp; }
	const int GetHp() const { return hp; }

	VECTOR GetKnockBackDir()const { return knockBackDir; }
	void SetKnockBackDir(const VECTOR& direction) { knockBackDir = direction; }

	int GetHitPoint()const { return hp; }
	int SetHitPoint(int newHp){ hp = newHp; }
	void ApplyDamage(int damage) { hp -= damage; }

	const bool GetIsDead()const { return isDead; }
	void Kill() { isDead = true; }

	VECTOR GetToPlayerDirection();
	bool IsPlayerInRange(float range);

	void SetPlayer(const std::weak_ptr<Player>& player) { m_pPlayer = player; }

protected:
	void Move();				// 移動処理

	StateMachine stateMachine;	// ステートマシン

	VECTOR knockBackDir = { 0.0f,0.0f,0.0f };	// ノックバックの方向

	bool isDamage = false;
	bool isDead = false;

	int hp = 0;

	std::weak_ptr<Player> m_pPlayer;

};