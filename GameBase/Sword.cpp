#include "stdafx.h"
#include "Sword.h"
#include "Player.h"

void Sword::Init()
{
	modelScale = VGet(0.005f, 0.005f, 0.005f);
    isCollisionEnabled = true;
}

void Sword::Load()
{
	modelHandle = MV1LoadModel("data/model/item/Heat-KatanaV2.mv1");

    bladeStartIndex = MV1SearchFrame(modelHandle, "Blade");
    bladeEndIndex = MV1SearchFrame(modelHandle, "Blade_end");
}

void Sword::Update()
{
    // 手の行列を取得（位置+回転）
    MATRIX handMat = owner->GetHandMatrix();

    // 武器用のスケール行列を作成
    MATRIX scaleMat = MGetScale(modelScale);

    // 行列を合成（スケール → 手の行列）
    MATRIX finalMat = MMult(scaleMat, handMat);

    // 武器にセット
    MV1SetMatrix(modelHandle, finalMat);
    
}

void Sword::Draw()
{
	MV1DrawModel(modelHandle);
}

const VECTOR Sword::GetCapsuleAPos()
{
    // 刀身のボーンの初めのマトリックスを取得
    MATRIX BladeStartMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, bladeStartIndex);
    // 座標をベクトル型に変換
    VECTOR CapsuleAPos = VGet(BladeStartMatrix.m[3][0], BladeStartMatrix.m[3][1], BladeStartMatrix.m[3][2]);
    return CapsuleAPos;   
}

const VECTOR Sword::GetCapsuleBPos()
{
    // 刀身のボーンの先端のマトリックスを取得
    MATRIX BladeEndMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, bladeEndIndex);
    // 座標をベクトル型に変換
    VECTOR CapsuleBPos = VGet(BladeEndMatrix.m[3][0], BladeEndMatrix.m[3][1], BladeEndMatrix.m[3][2]);
    return CapsuleBPos;
}
