#include "stdafx.h"
#include "EnemyBig.h"
#include "EnemyBig_StandState.h"
#include "EnemyBig_FallState.h"

void EnemyBig::Init()
{
	modelScale = params.scale;
	isStageCollisionEnabled = true;
	isCollisionEnabled = true;
	isShadowEnabled = true;
	hp = params.MaxHp;
	MaxHp = params.MaxHp;
	hpBarHeightOffset = params.HPBarHeight;

	hitHeight = params.HitHeight;
	hitRadius = params.HitRadius;

}

void EnemyBig::Load()
{
	// モデルハンドル取得
	modelHandle = MV1LoadModel("data/model/character/robot.mv1");
	MV1SetScale(modelHandle, modelScale);
	handBoneIndex = MV1SearchFrame(modelHandle, "mixamorig:LeftHand");
	headIndex = MV1SearchFrame(modelHandle, "mixamorig:Head_Center");

	// アニメーションのロード
	animation.LoadAnimation(modelHandle);
	// アイドルを再生
	animation.Play(static_cast<int>(EnemyBigAnimState::Idle), true);
}

void EnemyBig::Update()
{
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// ステートの更新
	stateMachine.Update();

	// 次の座標を計算
	Move();

	if (hp <= 0)
	{
		isDead = true;
	}

	// アニメーションの更新
	animation.Update();

	// 角度更新
	UpdateAngle();

	handPos = MV1GetFramePosition(modelHandle, handBoneIndex);
	lockOnPos = MV1GetFramePosition(modelHandle, headIndex);
}


void EnemyBig::ChangeState(std::shared_ptr<EnemyBigStateBase> a_spState)
{
	a_spState->SetOwner(this);
	stateMachine.ChangeState(a_spState);
}

/// <summary>
/// 天井に当たった時
/// </summary>
void EnemyBig::OnHitRoof()
{
	// Ｙ軸方向の速度は反転
	currentJumpPower = -currentJumpPower;
}

/// <summary>
/// 床に当たった時
/// </summary>
void EnemyBig::OnHitFloor()
{
	// ステートの変更
	if (isJumping)
	{
		auto spStandState = std::make_shared<EnemyBig_StandState>();
		ChangeState(spStandState);
	}

	// Ｙ軸方向の移動速度は０に
	currentJumpPower = 0.0f;
	isJumping = false;


}

/// <summary>
/// 落下が確定したとき
/// </summary>
void EnemyBig::OnFall()
{
	if (!isJumping)
	{
		// ジャンプ中(落下中）にする
		auto spFallState = std::make_shared<EnemyBig_FallState>();
		ChangeState(spFallState);
		isJumping = true;

		// ちょっとだけジャンプする
		currentJumpPower = FallUpPower;
	}
}
