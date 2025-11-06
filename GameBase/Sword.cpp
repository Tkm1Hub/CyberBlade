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
    // Player の手のボーンの行列を毎フレーム取得
    MATRIX handMat = MV1GetFrameLocalWorldMatrix(owner->GetModelHandle(), owner->GetHandBoneIndex());
    // Playerの鞘のボーンの行列を取得
    MATRIX swordSocketMat = MV1GetFrameLocalWorldMatrix(owner->GetModelHandle(), owner->GetSwordSocketBoneIndex());

    // 武器用のスケール行列を作成
    MATRIX scaleMat = MGetScale(modelScale);

    // 行列を合成（スケール → 手の行列）
    MATRIX finalMat = MMult(scaleMat, swordSocketMat);

    // 武器にセット
    MV1SetMatrix(modelHandle, finalMat);
    
}

void Sword::Draw()
{
	MV1DrawModel(modelHandle);
}

const VECTOR Sword::GetTopPos()
{
    // 刀身のボーンの先端のマトリックスを取得
    MATRIX BladeEndMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, bladeEndIndex);
    // 座標をベクトル型に変換
    VECTOR CapsuleAPos = VGet(BladeEndMatrix.m[3][0], BladeEndMatrix.m[3][1], BladeEndMatrix.m[3][2]);
    return CapsuleAPos;   
}

const VECTOR Sword::GetBottomPos()
{
    // 刀身のボーンの持ち手側のマトリックスを取得
    MATRIX BladeStartMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, bladeStartIndex);
    // 座標をベクトル型に変換
    VECTOR CapsuleBPos = VGet(BladeStartMatrix.m[3][0], BladeStartMatrix.m[3][1], BladeStartMatrix.m[3][2]);
    return CapsuleBPos;
}
