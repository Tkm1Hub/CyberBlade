#pragma once
#include "GameObject.h"
#include "Animation.h"

class Character :public IGameObject
{
public:
	Character(const std::string& name):IGameObject(name){}

	const float GetCurrentJumpPower() const { return currentJumpPower; }
	const float GetCurrentMoveSpeed() const { return currentMoveSpeed; }

	// 攻撃フラグ
	void SetAttackFrag(bool flag) { isAttack = flag; }
	const bool GetIsAttack()const { return isAttack; }

	void SetMoveVec(VECTOR newMoveVec) { moveVec = newMoveVec; }
	void SetJumpPower(float newJumpPower) { currentJumpPower = newJumpPower; }
	void SetMoveSpeed(float newMoveSpeed) { currentMoveSpeed = newMoveSpeed; }
	void SetTargetMoveDirection(VECTOR newDir) { targetMoveDirection = newDir; }

	void SetMoveFlag(bool IsMove) { isMove = IsMove; }
	void SetIsJumping(bool Isjumping) { isJumping = Isjumping; }

	const VECTOR GetTopPos()override {
		VECTOR CapsuleA = VGet(pos.x, pos.y + hitHeight, pos.z);
		return CapsuleA;
	}
	const VECTOR GetBottomPos()override {
		VECTOR CapsuleB = VGet(pos.x, pos.y + hitRadius, pos.z);
		return CapsuleB;
	}

	const VECTOR& GetModelForward() const { return modelForward; }

	Animation animation;		// アニメーション

protected:
	// 定数
	static constexpr float	FallUpPower = 0.05f;			// 足を踏み外した時のジャンプ力

	// キャラクター用変数
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);				// 移動ベクトル
	VECTOR targetMoveDirection = VGet(0.0f, 0.0f, 0.0f);	// 目標の移動方向のベクトル
	VECTOR modelForward = VGet(0.0f, 0.0f, 0.0f);			// モデルの方向ベクトル
	float currentMoveSpeed = 0.0f;							// 現在の移動速度
	float currentJumpPower = 0.0f;							// Y軸方向の速度
	float hitHeight = 0.0f;
	float hitRadius = 0.0f;

	bool isMove = false;									// 移動中か
	bool isAttack = false;									// 攻撃中か
};