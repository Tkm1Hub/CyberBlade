#include "stdafx.h"
#include "EnemySmall.h"
#include "EnemySmall_StandState.h"
#include "EnemySmall_FallState.h"

void EnemySmall::Init()
{
	modelScale = VGet(0.1f, 0.1f, 0.1f);
	isStageCollisionEnabled = true;
	isCollisionEnabled = true;
	isShadowEnabled = true;

	pos = params.InitPos;

	auto spStandState = std::make_shared<EnemySmall_StandState>();
	ChangeState(spStandState);
	hitHeight = params.HitHeight;
	hitRadius = params.HitRadius;

}

void EnemySmall::Load()
{
	// ���f���n���h���擾
	modelHandle = MV1LoadModel("data/model/character/robot.mv1");
	MV1SetScale(modelHandle, modelScale);
	MV1SetPosition(modelHandle, params.InitPos);
}

void EnemySmall::Update()
{
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// �X�e�[�g�̍X�V
	stateMachine.Update();

	// ���̍��W���v�Z
	Move();
}


void EnemySmall::ChangeState(std::shared_ptr<EnemySmallStateBase> a_spState)
{
	a_spState->SetOwner(this);
	stateMachine.ChangeState(a_spState);
}

/// <summary>
/// �V��ɓ���������
/// </summary>
void EnemySmall::OnHitRoof()
{
	// �x�������̑��x�͔��]
	currentJumpPower = -currentJumpPower;
}

/// <summary>
/// ���ɓ���������
/// </summary>
void EnemySmall::OnHitFloor()
{
	// �X�e�[�g�̕ύX
	if (isJumping)
	{
		auto spStandState = std::make_shared<EnemySmall_StandState>();
		ChangeState(spStandState);
	}

	// �x�������̈ړ����x�͂O��
	currentJumpPower = 0.0f;
	isJumping = false;

	
}

/// <summary>
/// �������m�肵���Ƃ�
/// </summary>
void EnemySmall::OnFall()
{
	if (!isJumping)
	{
		// �W�����v��(�������j�ɂ���
		auto spFallState = std::make_shared<EnemySmall_FallState>();
		ChangeState(spFallState);
		isJumping = true;

		// ������Ƃ����W�����v����
		currentJumpPower = FallUpPower;
	}
}
