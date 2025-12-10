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

	const VECTOR& GetTargetAngle() { return targetAngle; }
	void SetTargetAngle(VECTOR dir) { targetAngle = dir; }

	const bool GetIsAlert() const { return isAlert;}
	void SetIsAlert(bool flag) { isAlert = flag; }

	const float GetHandHitRadius() { return handHitRadius; }

	VECTOR GetToPlayerDirection();
	bool IsPlayerInRange(float range);
	VECTOR GetPlayerPos();

	void SetPlayer(const std::weak_ptr<Player>& player) { m_pPlayer = player; }

	// 手のボーン
	const VECTOR GetHandPos()const { return handPos; }
	const int GetHandBoneIndex() const { return handBoneIndex; }

	// 頭のボーン
	const VECTOR GetHeadPos()const { return headPos; }

protected:
	void Move();				// 移動処理
	void UpdateAngle();			// モデルの角度更新
	float angleSpeed = 0.2f;	// 角度更新速度
	VECTOR targetAngle = { 0.0f,0.0f,0.0f };	// 目標方向ベクトル

	StateMachine stateMachine;	// ステートマシン

	int handBoneIndex = -1;		// 手のボーンの番号
	float handHitRadius = 0.0f;	// 手の当たり判定の半径
	VECTOR handPos = { 0.0f,0.0f,0.0f };		// 手のボーンの座標

	int headBoneIndex = -1;					// 頭のボーン番号
	VECTOR headPos = { 0.0f,0.0f,0.0f };	// 頭の座標

	float attackCollisionRadius = 0.0f;				// 攻撃の当たり判定の半径
	VECTOR attackCollisionPos = { 0.0f,0.0f,0.0f };	// 攻撃の当たり判定の座標

	bool isAlert = false;	// 警戒状態

	float m_Gravity = 0.2f;	// 重力


	float hpBarHeightOffset = 0.0f;				// HPゲージを表示する高さ

	std::weak_ptr<Player> m_pPlayer;

};