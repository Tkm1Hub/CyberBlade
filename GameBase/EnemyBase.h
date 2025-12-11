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

	const float GetHandHitRadius() { return LeftHandHitRadius; }

	VECTOR GetToPlayerDirection();
	bool IsPlayerInRange(float range);
	VECTOR GetPlayerPos();

	void SetPlayer(const std::weak_ptr<Player>& player) { m_pPlayer = player; }

	// 手のボーン
	const VECTOR GetLeftHandPos()const { return LeftHandPos; }
	const int GetLeftHandBoneIndex() const { return LeftHandBoneIndex; }

	const VECTOR GetRightHandPos()const { return RightHandPos; }
	const int GetRightHandBoneIndex() const { return RightHandBoneIndex; }

	// 頭のボーン
	const VECTOR GetHeadPos()const { return headPos; }

	// 腰のボーン
	const VECTOR GetHipPos()const { return hipPos; }
	const int GetHipBoneIndex() const { return hipBoneIndex; }

	// 攻撃の当たり判定
	const VECTOR GetAttackCollisionPos() const { return attackCollisionPos; }
	void SetAttackCollisionPos(VECTOR pos) { attackCollisionPos = pos; }
	const float GetAttackCollisionRadius()const { return attackCollisionRadius; }
	void SetAttackCollisionRadius(float radius) { attackCollisionRadius = radius; }

protected:
	void Move();				// 移動処理
	void UpdateAngle();			// モデルの角度更新
	float angleSpeed = 0.2f;	// 角度更新速度
	VECTOR targetAngle = { 0.0f,0.0f,0.0f };	// 目標方向ベクトル

	StateMachine stateMachine;	// ステートマシン

	int LeftHandBoneIndex = -1;		// 左手のボーンの番号
	float LeftHandHitRadius = 0.0f;	// 左手の当たり判定の半径
	VECTOR LeftHandPos = { 0.0f,0.0f,0.0f };		// 左手のボーンの座標

	int RightHandBoneIndex = -1;	// 右手のボーンの番号
	float RightHandHitRadius = 0.0f;	// 右手の当たり判定の半径
	VECTOR RightHandPos = { 0.0f,0.0f,0.0f };		// 右手のボーンの座標

	int headBoneIndex = -1;					// 頭のボーン番号
	VECTOR headPos = { 0.0f,0.0f,0.0f };	// 頭の座標

	int hipBoneIndex = -1;					// 腰のボーン番号
	float hipHitRadius = 0.0f;				// 腰の当たり判定
	VECTOR hipPos = { 0.0f,0.0f,0.0f };		// 腰の座標

	float attackCollisionRadius = 0.0f;				// 攻撃の当たり判定の半径
	VECTOR attackCollisionPos = { 0.0f,0.0f,0.0f };	// 攻撃の当たり判定の座標

	bool isAlert = false;	// 警戒状態

	float m_Gravity = 0.2f;	// 重力


	float hpBarHeightOffset = 0.0f;				// HPゲージを表示する高さ

	std::weak_ptr<Player> m_pPlayer;

};