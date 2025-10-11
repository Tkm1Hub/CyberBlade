#include "stdafx.h"
#include "ShadowManager.h"

void ShadowManager::Init()
{
	shadowMapHandle = MakeShadowMap(SHADOW_QUALITY, SHADOW_QUALITY);
	lightDirection = VGet(0.5f, -1.0f, -0.5f);

	// ライトの方向を設定
	SetLightDirection(lightDirection);

	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection(shadowMapHandle, lightDirection);
}

void ShadowManager::Update(const VECTOR& pos)
{

	//シャドウを描画する範囲を指定
	VECTOR minPos = VSub(pos, VGet(drawShadowRadius, drawShadowHeight, drawShadowRadius));
	VECTOR maxPos = VAdd(pos, VGet(drawShadowRadius, drawShadowHeight, drawShadowRadius));

	SetShadowMapDrawArea(shadowMapHandle, minPos, maxPos);
}