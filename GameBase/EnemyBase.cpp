#include "stdafx.h"
#include "EnemyBase.h"


void EnemyBase::Move()
{
	// HACK: �ړ�������0.01�����Ŕ����Ɉړ����Ă����ꍇ�͂�����ړ����ăo�O��
	// x����y�������� 0.01f �ȏ�ړ������ꍇ�́u�ړ������v�t���O���P�ɂ���
	if (fabs(moveVec.x) > 0.01f || fabs(moveVec.z) > 0.01f)
	{
		isMove = true;
	}
	else
	{
		isMove = false;
	}

	moveVec = VScale(moveVec, currentMoveSpeed);

	// �ړ��x�N�g���̂x�������x�������̑��x�ɂ���
	moveVec.y = currentJumpPower;

	nextPos = VAdd(pos, moveVec);

}


void EnemyBase::Draw()
{
	MV1DrawModel(modelHandle);
}
