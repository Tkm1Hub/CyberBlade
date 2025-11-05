#include "stdafx.h"
#include "EnemyBase.h"
#include "Player.h"

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

// プレイヤーのへの方向ベクトルを取得
VECTOR EnemyBase::GetToPlayerDirection()
{
	if (auto p = m_pPlayer.lock())
	{
		VECTOR EnemyPos = pos;
		VECTOR PlayerPos = p->GetPosition();

		VECTOR dir = VSub(PlayerPos, EnemyPos);
		dir.y = 0.0f;
		dir = VNorm(dir);

		return dir;
	}

	// プレイヤーが存在しない場合
	return VGet(0.0f, 0.0f, 0.0f);
}

// プレイヤーが一定範囲内にいるかどうか取得
bool EnemyBase::IsPlayerInRange(float range)
{
	if (auto p = m_pPlayer.lock())
	{
		VECTOR PlayerPos = p->GetPosition();
		VECTOR EnemyPos = pos;

		VECTOR direction = VSub(PlayerPos, EnemyPos);
		float distance = VSize(direction);

		// 距離が範囲内かどうかを返す
		return distance <= range;
	}

	// プレイヤーが存在しない場合
	return false;
}