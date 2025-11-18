#pragma once
#include "Character.h"
#include "StateMachine.h"

class Player;
class EnemyBase :public Character
{
public:
	EnemyBase(const std::string& name) :Character(name) {}

	void Draw() override;


	void SetHp(int newHp) { hp = newHp; }
	const int GetHp() const { return hp; }



	const VECTOR GetHPBarPos()const;


	const bool GetIsAlert() const { return isAlert;}
	void SetIsAlert(bool flag) { isAlert = flag; }

	const float GetHandHitRadius() { return handHitRadius; }

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
	float handHitRadius = 0.0f;	// 手の当たり判定の半径

	VECTOR handPos = { 0.0f,0.0f,0.0f };		// 手のボーンの座標

	bool isAlert = false;	// 警戒状態

	float hpBarHeightOffset = 0.0f;				// HPゲージを表示する高さ

	std::weak_ptr<Player> m_pPlayer;

};