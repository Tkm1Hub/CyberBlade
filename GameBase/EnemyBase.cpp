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

void EnemyBase::UpdateAngle()
{
	if (!isAlert && !isMove) return;
	// プレイヤーの移動方向にモデルの方向を近づける
	float targetAngle;			// 目標角度
	float difference;			// 目標角度と現在の角度との差
	float speed = angleSpeed;	// 角度変更速度


	// 目標の方向ベクトルから角度値を算出する
	if (isAlert)
	{
		VECTOR targetVec = GetToPlayerDirection();
		targetAngle = static_cast<float>(atan2(targetVec.x, targetVec.z));
	}
	else
	{
		VECTOR targetVec = moveVec;
		targetVec.y = 0.0f;
		targetVec = VNorm(targetVec);

		targetAngle = static_cast<float>(atan2(targetVec.x, targetVec.z));
	}

	// 目標の角度と現在の角度との差を割り出す
	// 最初は単純に引き算
	difference = targetAngle - angleH;

	// ある方向からある方向の差が１８０度以上になることは無いので
	// 差の値が１８０度以上になっていたら修正する
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	// 角度の差が０に近づける
	if (difference > 0.0f)
	{
		// 差がプラスの場合は引く
		difference -= speed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else
	{
		// 差がマイナスの場合は足す
		difference += speed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	// モデルの角度を更新
	angleH = targetAngle - difference;

	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angleH + DX_PI_F, 0.0f));
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