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
	const int GetMaxHp() const { return MaxHp; }

	VECTOR GetKnockBackDir()const { return knockBackDir; }
	void SetKnockBackDir(const VECTOR& direction) { knockBackDir = direction; }

	int GetHitPoint()const { return hp; }
	int SetHitPoint(int newHp){ hp = newHp; }
	void ApplyDamage(int damage) { hp -= damage; }

	const VECTOR GetHPBarPos()const;

	const bool GetIsDead()const { return isDead; }
	void Kill() { isDead = true; }

	const bool GetIsAlert() const { return isAlert;}
	void SetIsAlert(bool flag) { isAlert = flag; }

	VECTOR GetToPlayerDirection();
	bool IsPlayerInRange(float range);

	void SetPlayer(const std::weak_ptr<Player>& player) { m_pPlayer = player; }

	// 手のボーン
	const VECTOR GetHandPos()const { return handPos; }
	const int GetHandBoneIndex() const { return handBoneIndex; }

protected:
	void Move();				// 移動処理
	void UpdateAngle();			// モデルの角度更新
	float angleSpeed = 0.2f;	// 角度更新速度

	StateMachine stateMachine;	// ステートマシン

	int handBoneIndex = -1;		// 手のボーンの番号

	VECTOR knockBackDir = { 0.0f,0.0f,0.0f };	// ノックバックの方向
	VECTOR handPos = { 0.0f,0.0f,0.0f };		// 手のボーンの座標

	bool isDamage = false;
	bool isDead = false;
	bool isAlert = false;	// 警戒状態

	int hp = 0;
	int MaxHp = 0;
	float hpBarHeightOffset = 0.0f;				// HPゲージを表示する高さ

	std::weak_ptr<Player> m_pPlayer;

};