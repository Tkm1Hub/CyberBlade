#include "stdafx.h"
#include "Stage.h"

void Stage::Init()
{
	pos = VGet(0.0f, -10.0f, 10.0f);
	modelScale = VGet(0.13f, 0.13f, 0.13f);
	isShadowEnabled = true;
}

void Stage::Load()
{
	// �X�e�[�W���f��
	modelHandle = MV1LoadModel("data/model/stage/Stage_Draw.mv1");
	MV1SetScale(modelHandle, modelScale);
	MV1SetPosition(modelHandle, pos);

	// �����蔻��p���f��
	collisionModelHandle = MV1LoadModel("data/model/stage/Stage_Collision.mv1");
	MV1SetScale(collisionModelHandle, modelScale);
	MV1SetPosition(collisionModelHandle, pos);
}

void Stage::Draw()
{
	MV1DrawModel(modelHandle);
}