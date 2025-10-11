#include "stdafx.h"
#include "MainCamera.h"

void MainCamera::Init()
{
	pos = VGet(0.0f, 50.0f, -30.0f);
	currentTarget = VGet(0.0f, 30.0f, 0.1f);
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
}

void MainCamera::Update()
{
	moveSmoothing();

	// �J�����̕�����ۑ�
	forward = VSub(pos, currentTarget);
	forward.y = 0.0f;
	forward = VNorm(forward);

	// �ʒu�ƒ����_�̐ݒ�
	SetCameraPositionAndTarget_UpVecY(pos, currentTarget);
}

// �J�����̍��W�ƃ^�[�Q�b�g��ݒ�
void MainCamera::SetCameraPositionAndTarget(const VECTOR& newPos, const VECTOR& newTarget)
{
	nextPosition = newPos;
	nextTarget = newTarget;
}

/// <summary>
/// �X���[�Y�Ɉړ�
/// </summary>
void MainCamera::moveSmoothing()
{
	// �ڕW�n�_�ƌ��݈ʒu�̍����擾
	VECTOR diff = VSub(nextPosition, pos);
	VECTOR targetDiff = VSub(nextTarget, currentTarget);

	// ���ɃX���[�W���O��������
	diff = VScale(diff, SMOOTHING);
	targetDiff = VScale(targetDiff, SMOOTHING);

	// ���݈ʒu�ɉ��Z
	pos = VAdd(pos, diff);
	currentTarget = VAdd(currentTarget, targetDiff);
}