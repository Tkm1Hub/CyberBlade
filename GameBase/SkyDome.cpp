#include "stdafx.h"
#include "SkyDome.h"
#include "Player.h"
void SkyDome::Init()
{
	modelScale = VGet(0.8f, 0.8f, 0.8f);
}

void SkyDome::Load()
{
	modelHandle = MV1LoadModel("data/model/stage/SkyDome_Sunny.mv1");
	MV1SetScale(modelHandle, scale);
	MV1SetPosition(modelHandle, pos);
}

void SkyDome::Update()
{
	pos = VGet(owner->GetPosition().x, 0.0f, owner->GetPosition().z);
	MV1SetPosition(modelHandle, pos);
}

void SkyDome::Draw()
{
	MV1DrawModel(modelHandle);
}