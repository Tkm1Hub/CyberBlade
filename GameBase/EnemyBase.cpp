#include "stdafx.h"
#include "EnemyBase.h"


void EnemyBase::Move()
{
	// HACK: 移動距離が0.01未満で微妙に移動していた場合はじんわり移動してバグる
	// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
	if (fabs(moveVec.x) > 0.01f || fabs(moveVec.z) > 0.01f)
	{
		isMove = true;
	}
	else
	{
		isMove = false;
	}

	moveVec = VScale(moveVec, currentMoveSpeed);

	// 移動ベクトルのＹ成分をＹ軸方向の速度にする
	moveVec.y = currentJumpPower;

	nextPos = VAdd(pos, moveVec);

}


void EnemyBase::Draw()
{
	MV1DrawModel(modelHandle);
}
