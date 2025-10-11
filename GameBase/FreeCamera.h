#pragma once
#include "VirtualCameraBase.h"

class Player;
class FreeCamera : public VirtualCameraBase
{
public:
	FreeCamera(const std::string& name): VirtualCameraBase(name){}

	void SetPlayer(const std::weak_ptr<Player>& playerPtr);

	void Init();
	void Update() override;

private:

	// �萔
	static constexpr float MAX_ANGLE_SPEED = 0.04f;		// �ő���񑬓x
	static constexpr float ANGLESPEED = 0.03f;			// �J�������x
	static constexpr float ACCEL = 0.01f;				// �J���������x
	static constexpr float DECEL = 0.005f;				// �J���������x
	static constexpr float LOOK_OFFSET_Y = 20.0f;		// �����_�̍���
	static constexpr float DISTANCE_OFFSET = 40.0f;		// �v���C���[����̋���

	// �ϐ�
	float currentAngleSpeed = 0.0f;						// ���݂̃J�������񑬓x
	float angleH = 0.0f;								// �����p�x
	float angleV = 0.0f;								// �����p�x
	bool isMoveAngle = false;							// �J�������ړ�����

	std::weak_ptr<Player> player;

	void CalcCameraAngle();		// �J�����̃A���O�����v�Z
	float CalcAngleSpeed();		// �J�����̐��񑬓x���v�Z
	void FixCameraPosition();	// �J�������W��␳����
};