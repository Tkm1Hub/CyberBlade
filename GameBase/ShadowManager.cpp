#include "stdafx.h"
#include "ShadowManager.h"

void ShadowManager::Init()
{
	shadowMapHandle = MakeShadowMap(SHADOW_QUALITY, SHADOW_QUALITY);
	lightDirection = VGet(0.5f, -1.0f, -0.5f);

	// ���C�g�̕�����ݒ�
	SetLightDirection(lightDirection);

	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection(shadowMapHandle, lightDirection);
}

void ShadowManager::Update(const VECTOR& pos)
{

	//�V���h�E��`�悷��͈͂��w��
	VECTOR minPos = VSub(pos, VGet(drawShadowRadius, drawShadowHeight, drawShadowRadius));
	VECTOR maxPos = VAdd(pos, VGet(drawShadowRadius, drawShadowHeight, drawShadowRadius));

	SetShadowMapDrawArea(shadowMapHandle, minPos, maxPos);
}