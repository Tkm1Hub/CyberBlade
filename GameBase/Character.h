#pragma once
#include "GameObject.h"

class Character :public IGameObject
{
public:
	Character(const std::string& name):IGameObject(name){}

	float GetCurrentJumpPower() { return currentJumpPower; }
	float GetCurrentMoveSpeed() { return currentMoveSpeed; }

	void SetMoveVec(VECTOR newMoveVec) { moveVec = newMoveVec; }
	void SetJumpPower(float newJumpPower) { currentJumpPower = newJumpPower; }
	void SetMoveSpeed(float newMoveSpeed) { currentMoveSpeed = newMoveSpeed; }

	void SetMoveFlag(bool IsMove) { isMove = IsMove; }
	void SetIsJumping(bool Isjumping) { isJumping = Isjumping; }

	const VECTOR GetCapsuleAPos()override {
		VECTOR CapsuleA = VGet(pos.x, pos.y + hitHeight, pos.z);
		return CapsuleA;
	}
	const VECTOR GetCapsuleBPos()override {
		VECTOR CapsuleB = VGet(pos.x, pos.y + hitRadius, pos.z);
		return CapsuleB;
	}

protected:
	// 定数
	static constexpr float	FallUpPower = 0.05f;			// 足を踏み外した時のジャンプ力

	// キャラクター用変数
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);				// 移動ベクトル
	VECTOR targetMoveDirection = VGet(0.0f, 0.0f, 0.0f);	// モデルが向くべき方向のベクトル
	float angle = 0.0f;										// モデルの角度
	float currentMoveSpeed = 0.0f;							// 現在の移動速度
	float currentJumpPower = 0.0f;							// Y軸方向の速度
	float hitHeight = 0.0f;
	float hitRadius = 0.0f;

	bool isMove = false;
};