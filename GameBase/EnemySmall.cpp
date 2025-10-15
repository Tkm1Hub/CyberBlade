#include "stdafx.h"
#include "EnemySmall.h"
#include "EnemySmall_StandState.h"
#include "EnemySmall_FallState.h"

void EnemySmall::Init()
{
	modelScale = VGet(0.1f, 0.1f, 0.1f);
	isStageCollisionEnabled = true;
	isCollisionEnabled = true;
	isShadowEnabled = true;

	pos = params.InitPos;

	auto spStandState = std::make_shared<EnemySmall_StandState>();
	ChangeState(spStandState);
	hitHeight = params.HitHeight;
	hitRadius = params.HitRadius;

}

void EnemySmall::Load()
{
	// モデルハンドル取得
	modelHandle = MV1LoadModel("data/model/character/robot.mv1");
	MV1SetScale(modelHandle, modelScale);
	MV1SetPosition(modelHandle, params.InitPos);
}

void EnemySmall::Update()
{
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// ステートの更新
	stateMachine.Update();

	// 次の座標を計算
	Move();
}


void EnemySmall::ChangeState(std::shared_ptr<EnemySmallStateBase> a_spState)
{
	a_spState->SetOwner(this);
	stateMachine.ChangeState(a_spState);
}

/// <summary>
/// 天井に当たった時
/// </summary>
void EnemySmall::OnHitRoof()
{
	// Ｙ軸方向の速度は反転
	currentJumpPower = -currentJumpPower;
}

/// <summary>
/// 床に当たった時
/// </summary>
void EnemySmall::OnHitFloor()
{
	// ステートの変更
	if (isJumping)
	{
		auto spStandState = std::make_shared<EnemySmall_StandState>();
		ChangeState(spStandState);
	}

	// Ｙ軸方向の移動速度は０に
	currentJumpPower = 0.0f;
	isJumping = false;

	
}

/// <summary>
/// 落下が確定したとき
/// </summary>
void EnemySmall::OnFall()
{
	if (!isJumping)
	{
		// ジャンプ中(落下中）にする
		auto spFallState = std::make_shared<EnemySmall_FallState>();
		ChangeState(spFallState);
		isJumping = true;

		// ちょっとだけジャンプする
		currentJumpPower = FallUpPower;
	}
}
