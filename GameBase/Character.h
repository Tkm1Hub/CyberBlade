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
	// �萔
	static constexpr float	FallUpPower = 0.05f;			// ���𓥂݊O�������̃W�����v��

	// �L�����N�^�[�p�ϐ�
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);				// �ړ��x�N�g��
	VECTOR targetMoveDirection = VGet(0.0f, 0.0f, 0.0f);	// ���f���������ׂ������̃x�N�g��
	float angle = 0.0f;										// ���f���̊p�x
	float currentMoveSpeed = 0.0f;							// ���݂̈ړ����x
	float currentJumpPower = 0.0f;							// Y�������̑��x
	float hitHeight = 0.0f;
	float hitRadius = 0.0f;

	bool isMove = false;
};