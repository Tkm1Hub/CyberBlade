#pragma once
#include "GameObject.h"

class MainCamera :public IGameObject
{
public:
	MainCamera(const std::string& name) : IGameObject(name){}

	void Init() override;
	void Update() override;

	void SetCameraPositionAndTarget(const VECTOR& newPos, const VECTOR& newTarget);

	const VECTOR GetForward() const { return forward; }

private:
	// �萔
	static constexpr float CAMERA_NEAR = 0.1f;
	static constexpr float CAMERA_FAR = 1300.0f;
	static constexpr float SMOOTHING = 0.1f;			// �J�����̃X���[�W���O

	// �ϐ�
	VECTOR currentTarget = VGet(0.0f, 0.0f, 0.0f);		// �J���������_
	VECTOR nextTarget = VGet(0.0f, 0.0f, 0.0f);			// �J���������_�̖ڕW�ʒu
	VECTOR forward = VGet(0.0f, 0.0f, 0.0f);			// �J�����̕���
	VECTOR currentPosition = VGet(0.0f, 0.0f, 0.0f);	// ���݂̃|�W�V����
	VECTOR nextPosition = VGet(0.0f, 0.0f, 0.0f);		// �ڕW�̃|�W�V����
	float angleH = 0.0f;								// �����p�x
	float angleV = 0.0f;								// �������_
	float currentAngleSpeed = 0.0f;						// ���݂̃A���O���ύX���x
	bool isMoveAngle = false;							// �J�������ړ������ǂ���

	void moveSmoothing();	// �X���[�Y�ړ�
};