#include "stdafx.h"
#include "FreeCamera.h"
#include "Input.h"
#include "Player.h"

void FreeCamera::SetPlayer(const std::weak_ptr<Player>& playerPtr)
{
	player = playerPtr;
}

void FreeCamera::Init()
{
	name = "FreeCamera";
}

void FreeCamera::Update()
{
	if (auto p = player.lock())
	{
		VECTOR playerPos = p->GetPosition();

	// �J�����̐��񑬓x���v�Z
	currentAngleSpeed = CalcAngleSpeed();

	CalcCameraAngle();

	//�J�����̒����_�̓v���C���[���W����K��l���������W
	target = VAdd(playerPos, VGet(0.0f, LOOK_OFFSET_Y, 0.0f));

	// �J�����̍��W��␳����
	FixCameraPosition();

	printf("freeCameraPos[%.2f,%.2f,%.2f]\n", pos.x, pos.y, pos.z);
	}
}

void FreeCamera::CalcCameraAngle()
{
	// X��
	if (0.0f > Input::GetInput().GetRightStickX())
	{
		angleH -= currentAngleSpeed;
		// �P�W�O�x�ȏ�ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
		if (angleH > DX_PI_F)
		{
			angleH += DX_TWO_PI_F;
		}
	}
	else if (Input::GetInput().GetRightStickX() > 0.0f)
	{
		angleH += currentAngleSpeed;
		// �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
		if (angleH < -DX_PI_F)
		{
			angleH -= DX_TWO_PI_F;
		}
	}

	// Y��
	if (0.0f > Input::GetInput().GetRightStickY())
	{
		angleV += currentAngleSpeed;
		// ������p�x�ȉ��ɂ͂Ȃ�Ȃ��悤�ɂ���
		if (angleV > DX_PI_F * 0.5f - 0.6f)
		{
			angleV = DX_PI_F * 0.5f - 0.6f;
		}
	}
	else if (Input::GetInput().GetRightStickY() > 0.0f)
	{
		angleV -= currentAngleSpeed;
		// ������p�x�ȏ�ɂ͂Ȃ�Ȃ��悤�ɂ���
		if (angleV < -DX_PI_F * 0.5f + 0.6f)
		{
			angleV = -DX_PI_F * 0.5f + 0.6f;
		}
	}
}

float FreeCamera::CalcAngleSpeed()
{
	float stickAngle = Input::GetInput().GetRStickAngle();
	float stickPower = abs(stickAngle) / 1000.0f;

	// �X���ɉ������ő呬�x���v�Z
	float maxSpeed = MAX_ANGLE_SPEED * stickPower;

	// ���� or ����
	if (Input::GetInput().GetIsMoveRStick())
	{
		currentAngleSpeed += ACCEL; // ������
		currentAngleSpeed = min(currentAngleSpeed, maxSpeed); // maxSpeed�Ő���
	}
	else
	{
		currentAngleSpeed -= DECEL; // �����͌Œ�
		currentAngleSpeed = max(currentAngleSpeed, 0.0f); // �}�C�i�X�ɂȂ�Ȃ��悤��
	}

	// �t���O
	isMoveAngle = (currentAngleSpeed > 0.0f);

	return currentAngleSpeed;
}

void FreeCamera::FixCameraPosition()
{
	// ���������̉�]�͂x����]
	auto rotY = MGetRotY(angleH);

	// ���������̉�]�͂y����] )
	auto rotZ = MGetRotZ(angleV);

	// �J��������v���C���[�܂ł̏����������Z�b�g
	float cameraPlayerLength = DISTANCE_OFFSET;

	// �J�����̍��W���Z�o
	// �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
	// ����������]( �y����] )���������Ɛ���������]( �x����] )���čX��
	// �����_�̍��W�𑫂������̂��J�����̍��W
	pos = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ), rotY), target);

}
