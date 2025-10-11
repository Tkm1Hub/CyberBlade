#include "stdafx.h"
#include "StageCollision.h"

StageCollision::StageCollision() {}

void StageCollision::SetStageCollision(const int collisionModelHandle)
{
    modelHandle = collisionModelHandle;
}

/// <summary>
/// �����蔻������āA�␳�����ړ���̃|�W�V������Ԃ�
/// </summary>
VECTOR StageCollision::CheckCollision(IGameObject& object, const VECTOR& nextPos)
{
    VECTOR oldPos = object.GetPosition();       // �ړ��O�̍��W
    VECTOR newPos = nextPos;

    // �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
    // ( ���o����͈͈͂ړ��������l������ )
    auto hitDim = MV1CollCheck_Sphere(modelHandle, -1, oldPos, DefaultSize + VSize(newPos));

    // ���o���ꂽ�|���S�����ǃ|���S��( �w�y���ʂɐ����ȃ|���S�� )�����|���S��( �w�y���ʂɐ����ł͂Ȃ��|���S�� )���𔻒f���A�ۑ�����
    AnalyzeWallAndFloor(hitDim, oldPos);

    // �ǃ|���S���Ƃ̓�������`�F�b�N���A�ړ��x�N�g����␳����
    newPos = CheckHitWithWall(object, newPos);

    // ���|���S���Ƃ̓�������`�F�b�N���A�ړ��x�N�g����␳����
    newPos = CheckHitWithFloor(object, newPos);

    // ���o�����v���C���[�̎��͂̃|���S�������J������
    MV1CollResultPolyDimTerminate(hitDim);

    return newPos;
}

/// <summary>
/// ���o���ꂽ�|���S�����ǃ|���S��( �w�y���ʂɐ����ȃ|���S�� )�����|���S��( �w�y���ʂɐ����ł͂Ȃ��|���S�� )���𔻒f���A�ۑ�����
/// </summary>
void StageCollision::AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition)
{
    // �ǃ|���S���Ə��|���S���̐�������������
    wallNum = 0;
    floorNum = 0;

    // ���o���ꂽ�|���S���̐������J��Ԃ�
    for (int i = 0; i < hitDim.HitNum; i++)
    {
        const auto& poly = hitDim.Dim[i];
        // �w�y���ʂɐ������ǂ����̓|���S���̖@���̂x�������O�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
        if (poly.Normal.y < 0.000001f && poly.Normal.y > -0.000001f)
        {
            if ((poly.Position[0].y > checkPosition.y + 1.0f ||
                poly.Position[1].y > checkPosition.y + 1.0f ||
                poly.Position[2].y > checkPosition.y + 1.0f) && wallNum < MaxHitColl)
            {
                wall[wallNum++] = &hitDim.Dim[i];
            }
        }
        else
        {
            if (floorNum < MaxHitColl)
            {
                floor[floorNum++] = &hitDim.Dim[i];
            }
        }
    }
}

/// <summary>
/// �ǃ|���S���Ƃ̓�������`�F�b�N���A�␳���ׂ��ړ��x�N�g����Ԃ�
/// </summary>
VECTOR StageCollision::CheckHitWithWall(IGameObject& object, const VECTOR& checkPosition)
{
    VECTOR fixedPos = checkPosition;

    float HitRadius = object.GetHitRadius();
    float HitHeight = object.GetHitHeight();

    // �ǂ̐������������瑁�����^�[��
    if (wallNum == 0)
        return fixedPos;

    // �ǂ���̉����o�����������݂�ő吔�����J��Ԃ�
    for (int k = 0; k < HitTryNum; k++)
    {
        // ������\���̂���ǃ|���S����S�Č���
        bool isHitWall = false;
        for (int i = 0; i < wallNum; i++)
        {
            // i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
            auto poly = wall[i];

            // �v���C���[�Ɠ������Ă���Ȃ�
            if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, HitHeight, 0.0f)), HitRadius,
                poly->Position[0], poly->Position[1], poly->Position[2]))
            {
                // �K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
                // �ړ���̈ʒu���X�V�i�ړ���̏ꏊ��␳�j
                fixedPos = VAdd(fixedPos, VScale(poly->Normal, HitSlideLength));

                // �ړ������ǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
                for (int j = 0; j < wallNum; j++)
                {
                    // �������Ă����烋�[�v�𔲂���
                    auto checkPoly = wall[j];
                    if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, HitHeight, 0.0f)), HitRadius,
                        checkPoly->Position[0], checkPoly->Position[1], checkPoly->Position[2]))
                    {
                        isHitWall = true;
                        break;
                    }
                }

                // �S�Ẵ|���S���Ɠ������Ă��Ȃ������炱���Ń��[�v�I��
                if (!isHitWall) break;
            }
        }

        // �S���̃|���S���ŉ����o�������݂�O��
        // �S�Ă̕ǃ|���S���ƐڐG���Ȃ��Ȃ����烋�[�v���甲����
        if (!isHitWall)
            break;
    }

    return fixedPos;
}

/// <summary>
/// ���|���S���Ƃ̓�������`�F�b�N���A�␳���ׂ��ړ��x�N�g����Ԃ�
/// </summary>
VECTOR StageCollision::CheckHitWithFloor(IGameObject& object, const VECTOR& checkPosition)
{
    VECTOR fixedPos = checkPosition;
    float HitHeight = object.GetHitHeight();

    // ���̐������������瑁�����^�[��
    if (floorNum == 0)
        return fixedPos;

    float jumpPower = object.GetJumpPower();

    // �W�����v�����㏸���̏ꍇ�͏����𕪊�
    if (object.GetIsJumping() && jumpPower > 0.0f) // Jumping upward
    {
        // �V��ɓ����Ԃ��鏈�����s��
        // ��ԒႢ�V��ɂԂ���ׂ̔���p�ϐ���������
        bool isHitRoof = false;
        float minY = 0.0f;

        // ���|���S���̐������J��Ԃ�
        for (int i = 0; i < floorNum; i++)
        {
            auto poly = floor[i];   // i�Ԗڂ̏��|���S���̃A�h���X

            // ���悩�瓪�̍����܂ł̊ԂŃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
            // �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
            HITRESULT_LINE lineResult = HitCheck_Line_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, HitHeight, 0.0f)),
                poly->Position[0], poly->Position[1], poly->Position[2]);

            // �ڐG���Ă��Ȃ������牽�����Ȃ�
            if (lineResult.HitFlag)
            {
                // ���Ƀ|���S���ɓ������Ă��āA�����܂Ō��o�����V��|���S����荂���ꍇ�͉������Ȃ�
                if (!(isHitRoof && minY < lineResult.Position.y))
                {
                    // �|���S���ɓ��������t���O�𗧂Ă�
                    isHitRoof = true;

                    // �ڐG�����x���W��ۑ�����
                    minY = lineResult.Position.y;
                }
            }
        }

        // �ڐG�����|���S���������
        if (isHitRoof)
        {
            // �ڐG�����ꍇ�̓v���C���[�̂x���W��ڐG���W�����ɍX�V
            fixedPos.y = minY - HitHeight;
            object.OnHitRoof();
        }
    }
    // ���~�����W�����v���ł͂Ȃ��ꍇ�̏���
    else
    {
        bool isHitFloor = false;
        float maxY = 0.0f;

        // ���|���S���̐������J��Ԃ�
        for (int i = 0; i < floorNum; i++)
        {
            auto poly = floor[i];       // i�Ԗڂ̏��|���S���̃A�h���X

            // �W�����v�����ǂ����ŏ����𕪊�
            HITRESULT_LINE lineResult;  // �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����

            if (object.GetIsJumping())
            {
                // �W�����v���̏ꍇ�͓��̐悩�瑫���菭���Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�
                lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, HitHeight, 0.0f)),
                    VAdd(fixedPos, VGet(0.0f, -0.1f, 0.0f)),
                    poly->Position[0], poly->Position[1], poly->Position[2]);
            }
            else
            {
                // �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
                lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, HitHeight, 0.0f)),
                    VAdd(fixedPos, VGet(0.0f, -0.5f, 0.0f)),
                    poly->Position[0], poly->Position[1], poly->Position[2]);
            }

            // ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
            if (lineResult.HitFlag)
            {
                if (!(isHitFloor && maxY > lineResult.Position.y))
                {
                    // �ڐG�����x���W��ۑ�����
                    isHitFloor = true;
                    maxY = lineResult.Position.y;
                }
            }
        }

        // ���|���S���ɓ�������
        if (isHitFloor)
        {
            // �ڐG�����|���S���ň�ԍ����x���W���v���C���[�̂x���W�ɂ���
            fixedPos.y = maxY;

            // ���ɓ���������
            object.OnHitFloor();
        }
        else
        {
            // ���R���W�����ɓ������Ă��Ȃ��Ċ��W�����v��Ԃł͂Ȃ������ꍇ�͗������
            object.OnFall();
        }
    }

    return fixedPos;
}