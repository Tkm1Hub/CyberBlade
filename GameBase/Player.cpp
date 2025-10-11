#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "CameraManager.h"
#include "Player_StandState.h"
#include "Player_WalkState.h"
#include "Player_JumpState.h"
#include "Player_FallState.h"
#include "Player_RunState.h"

void Player::Init()
{
	modelScale = VGet(0.1f, 0.1f, 0.1f);
	isStageCollisionEnabled = true;
	isCollisionEnabled = true;
	isShadowEnabled = true;
	auto spStandState = std::make_shared<Player_StandState>();
	ChangeState(spStandState);
	hitHeight = params.HitHeight;
	hitRadius = params.HitRadius;
}

void Player::Load()
{
	// ���f���n���h���擾
	modelHandle = MV1LoadModel("data/model/character/Hideron.mv1");
	handBoneIndex = MV1SearchFrame(modelHandle, "Hand_R.001");
	MV1SetScale(modelHandle, modelScale);
	MV1SetPosition(modelHandle, pos);

	// �A�j���[�V�����̃��[�h
	animation.LoadAnimation(modelHandle);
	// �A�C�h�����Đ�
	animation.Play(static_cast<int>(PlayerAnimState::Idle));
}

void Player::Update()
{
	if (!isAttack)
	{
		// �X�e�B�b�N�ł̈ړ�����
		moveVec = GetMoveInput();
	}

	// �X�e�[�g�̍X�V
	stateMachine.Update();

	// ���̍��W���v�Z
	Move();

	// ���f���̕����X�V
	UpdateAngle();

	// �A�j���[�V�����̍X�V
	animation.Update();

	handMatrix = MV1GetFrameLocalWorldMatrix(modelHandle, handBoneIndex);
}

void Player::Draw()
{
	MV1DrawModel(modelHandle);
}

void Player::ChangeState(std::shared_ptr<PlayerStateBase> a_spState)
{
	a_spState->SetOwner(this);
	stateMachine.ChangeState(a_spState);
}

void Player::Move()
{
	// HACK: �ړ�������0.01�����Ŕ����Ɉړ����Ă����ꍇ�͂�����ړ����ăo�O��
// x����y�������� 0.01f �ȏ�ړ������ꍇ�́u�ړ������v�t���O���P�ɂ���
	if (fabs(moveVec.x) > 0.01f || fabs(moveVec.z) > 0.01f)
	{
		isMove = true;
	}
	else
	{
		isMove = false;
	}

	// �ړ����x���v�Z
	if (!isAttack)
	{
		CulcMoveSpeed();
	}
	moveVec = VScale(targetMoveDirection, currentMoveSpeed);

	// �ړ��x�N�g���̂x�������x�������̑��x�ɂ���
	moveVec.y = currentJumpPower;

	nextPos = VAdd(pos,moveVec);

	//Y���W��-100�ȉ��ɂȂ�������W������������
	if (pos.y < -1000.0f || pos.y>500)
	{
		pos = params.InitPos;
		nextPos = params.InitPos;
	}

	printf("targetMoveDirection [ %.2f,%.2f,%.2f ]\n", targetMoveDirection.x, targetMoveDirection.y, targetMoveDirection.z);
	printf("currentMoveSpeed : %f\n", currentMoveSpeed);
}

void Player::CulcMoveSpeed()
{
	if (isMove)
	{
		currentMoveSpeed += params.Accel;
	}
	else
	{
		currentMoveSpeed -= params.decel;
	}

	// ���E�l�𒴂�����C��
	if (isRunning)
	{
		currentMoveSpeed = std::clamp(currentMoveSpeed, 0.0f, params.RunSpeed);
	}
	else
	{
		currentMoveSpeed = std::clamp(currentMoveSpeed, 0.0f, params.WalkSpeed);
	}
}

void Player::UpdateAngle()
{
	// �v���C���[�̈ړ������Ƀ��f���̕������߂Â���
	float targetAngle;			// �ڕW�p�x
	float difference;			// �ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�
	float speed = params.AngleSpeed;	// �p�x�ύX���x


	// �ڕW�̕����x�N�g������p�x�l���Z�o����
	targetAngle = static_cast<float>(atan2(targetMoveDirection.x, targetMoveDirection.z));

	// �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
	// �ŏ��͒P���Ɉ����Z
	difference = targetAngle - angle;

	// ����������炠������̍����P�W�O�x�ȏ�ɂȂ邱�Ƃ͖����̂�
	// ���̒l���P�W�O�x�ȏ�ɂȂ��Ă�����C������
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	// �p�x�̍����O�ɋ߂Â���
	if (difference > 0.0f)
	{
		// �����v���X�̏ꍇ�͈���
		difference -= speed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else
	{
		// �����}�C�i�X�̏ꍇ�͑���
		difference += speed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	// ���f���̊p�x���X�V
	angle = targetAngle - difference;

	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// <summary>
/// �V��ɓ���������
/// </summary>
void Player::OnHitRoof()
{
	// �x�������̑��x�͔��]
	currentJumpPower = -currentJumpPower;
}

/// <summary>
/// ���ɓ���������
/// </summary>
void Player::OnHitFloor()
{
	// �x�������̈ړ����x�͂O��
	currentJumpPower = 0.0f;

	// �����W�����v���������ꍇ�͒��n��Ԃɂ���
	if (isJumping)
	{
		// �ړ����Ă������ǂ����Œ��n��̏�ԂƍĐ�����A�j���[�V�����𕪊򂷂�
		if (isMove)
		{
			if (isRunning)
			{
				auto spRunState = std::make_shared<Player_RunState>();
				ChangeState(spRunState);
			}
			else
			{
				auto spWalkState = std::make_shared<Player_WalkState>();
				ChangeState(spWalkState);
			}
		}
		else
		{
			auto spStandState = std::make_shared<Player_StandState>();
			ChangeState(spStandState);
		}

		// ���n���̓A�j���[�V�����̃u�����h�͍s��Ȃ�
		// animation->SetBlendRate(1.0f);
		isJumping = false;
	}
}

/// <summary>
/// �������m�肵���Ƃ�
/// </summary>
void Player::OnFall()
{
	if (!isJumping)
	{
		// �W�����v��(�������j�ɂ���
		auto spFallState = std::make_shared<Player_FallState>();
		ChangeState(spFallState);
		isJumping = true;

		// ������Ƃ����W�����v����
		currentJumpPower = FallUpPower;
	}
}

VECTOR Player::GetMoveInput()
{
	VECTOR mVec = VGet(0.0f, 0.0f, 0.0f);

	// �J�����̑O�����x�N�g�����擾
	VECTOR camForward = CameraManager::GetCameraManager().GetMainCamera()->GetForward();
	VECTOR camRight = VCross(camForward, VGet(0.0f, 1.0f, 0.0f));
	camRight = VNorm(camRight);

	// �X�e�B�b�N����
	float stickX = Input::GetInput().GetLeftStickX();
	float stickY = Input::GetInput().GetLeftStickY();

	// �ړ��x�N�g��
	mVec = VAdd(VScale(camRight, stickX), VScale(camForward, stickY));
	if (VSize(mVec) != 0.0f)
	{
		targetMoveDirection = VNorm(mVec);
	}

	return mVec;
}
