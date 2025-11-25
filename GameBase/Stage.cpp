#include "stdafx.h"
#include "Stage.h"

void Stage::Init()
{
	pos = VGet(0.0f, -10.0f, 10.0f);
	modelScale = VGet(0.07f, 0.07f, 0.07f);
	isShadowEnabled = true;
}

void Stage::Load()
{
	// ステージモデル
	modelHandle = MV1LoadModel("data/model/stage/HighWay.mv1");
	MV1SetScale(modelHandle, modelScale);
	MV1SetPosition(modelHandle, pos);

	// 当たり判定用モデル
	collisionModelHandle = MV1LoadModel("data/model/stage/Collision.mv1");
	MV1SetScale(collisionModelHandle, modelScale);
	MV1SetPosition(collisionModelHandle, pos);
}

void Stage::Draw()
{
	MV1DrawModel(modelHandle);
}