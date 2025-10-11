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
    // ��̍s����擾�i�ʒu+��]�j
    MATRIX handMat = owner->GetHandMatrix();

    // ����p�̃X�P�[���s����쐬
    MATRIX scaleMat = MGetScale(modelScale);

    // �s��������i�X�P�[�� �� ��̍s��j
    MATRIX finalMat = MMult(scaleMat, handMat);

    // ����ɃZ�b�g
    MV1SetMatrix(modelHandle, finalMat);
    
}

void Sword::Draw()
{
	MV1DrawModel(modelHandle);
}

const VECTOR Sword::GetCapsuleAPos()
{
    // ���g�̃{�[���̏��߂̃}�g���b�N�X���擾
    MATRIX BladeStartMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, bladeStartIndex);
    // ���W���x�N�g���^�ɕϊ�
    VECTOR CapsuleAPos = VGet(BladeStartMatrix.m[3][0], BladeStartMatrix.m[3][1], BladeStartMatrix.m[3][2]);
    return CapsuleAPos;   
}

const VECTOR Sword::GetCapsuleBPos()
{
    // ���g�̃{�[���̐�[�̃}�g���b�N�X���擾
    MATRIX BladeEndMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, bladeEndIndex);
    // ���W���x�N�g���^�ɕϊ�
    VECTOR CapsuleBPos = VGet(BladeEndMatrix.m[3][0], BladeEndMatrix.m[3][1], BladeEndMatrix.m[3][2]);
    return CapsuleBPos;
}
