#include "stdafx.h"
#include "Sword.h"
#include "Player.h"
#include "EffectManager.h"

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
    MATRIX finalMat;

    if (owner->GetIsSwordEpuipped())
    {
        finalMat = MMult(scaleMat, handMat);
    }
    else
    {
        finalMat = MMult(scaleMat, swordSocketMat);
    }

    if (owner->GetIsAttackEnabled())
    {
        SetIsCollisionEnabled(true);

        if (!isEnableEffect)
        {
            // 現在のアニメ番号によってエフェクトを再生
            int currentAnimNum = owner->animation.GetCurrentAnimNum();
            switch (currentAnimNum)
            {
            case (static_cast<int>(PlayerAnimState::AttackJump1)):
            {
                EffectManager::GetInstance().PlayEffect("SwordLine", owner->GetTopPos());
                EffectManager::GetInstance().SetRotation("SwordLine", MV1GetRotationXYZ(owner->GetModelHandle()));
                break;
            }
            case (static_cast<int>(PlayerAnimState::AttackJump2)):
            {
                EffectManager::GetInstance().PlayEffect("SwordLine2", owner->GetTopPos());
                EffectManager::GetInstance().SetRotation("SwordLine2", MV1GetRotationXYZ(owner->GetModelHandle()));
                break;
            }
            case (static_cast<int>(PlayerAnimState::Attack3)):
            {
                EffectManager::GetInstance().PlayEffect("SwordLine3", owner->GetTopPos());
                EffectManager::GetInstance().SetRotation("SwordLine3", MV1GetRotationXYZ(owner->GetModelHandle()));
                break;
            }
            default:
                return;
            }
            isEnableEffect = true;
        }
        //EffectManager::GetInstance().SetPosition("SwordLine", owner->GetTopPos());
        //EffectManager::GetInstance().SetRotation("SwordLine", MV1GetRotationXYZ(owner->GetModelHandle()));
    }
    else
    {
        SetIsCollisionEnabled(false);
        isEnableEffect = false;
    }

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

VECTOR Sword::GetRotationXYZFromMatrix(const MATRIX& mat)
{
    // 各軸ベクトル取得
    VECTOR x = VGet(mat.m[0][0], mat.m[0][1], mat.m[0][2]);
    VECTOR y = VGet(mat.m[1][0], mat.m[1][1], mat.m[1][2]);
    VECTOR z = VGet(mat.m[2][0], mat.m[2][1], mat.m[2][2]);

    // スケール除去（正規化）
    x = VNorm(x);
    y = VNorm(y);
    z = VNorm(z);

    MATRIX r = mat;
    r.m[0][0] = x.x; r.m[0][1] = x.y; r.m[0][2] = x.z;
    r.m[1][0] = y.x; r.m[1][1] = y.y; r.m[1][2] = y.z;
    r.m[2][0] = z.x; r.m[2][1] = z.y; r.m[2][2] = z.z;

    VECTOR rot;

    float sy = -r.m[2][0];
    sy = max(-1.0f, min(1.0f, sy));

    rot.y = asinf(sy);

    if (fabsf(cosf(rot.y)) > 0.0001f)
    {
        rot.x = atan2f(r.m[2][1], r.m[2][2]);
        rot.z = atan2f(r.m[1][0], r.m[0][0]);
    }
    else
    {
        // ジンバルロック
        rot.x = atan2f(-r.m[1][2], r.m[1][1]);
        rot.z = 0.0f;
    }

    return rot; // ラジアン}
}