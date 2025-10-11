#pragma once
#include "Character.h"
#include "StateMachine.h"
#include "Animation.h"
#include "PlayerStateBase.h"

// �p�����[�^
struct PlayerParams
{
	float JumpPower = 2.5f;		// �W�����v��
	float Gravity = 0.08f;		// �d��
	float WalkSpeed = 0.5f;		// �����ړ����x
	float RunSpeed = 1.5f;		// ����ړ����x
	float Attack1MoveSpeed = 0.7f;	// �U��1�i�K�ڂł̑O���ړ����x
	float Attack2MoveSpeed = 0.9f;	// �U��2�i�K�ڂł̑O���ړ����x
	float Attack3MoveSpeed = 0.5f;	// �U��3�i�K�ڂł̑O���ړ����x
	float AttackDashMoveSpeed = 1.5f;	// ����U���ł̑O���ړ����x
	float Accel = 0.01f;		// �ړ������x
	float decel = 0.03f;		// �ړ������x
	float AngleSpeed = 0.2f;	// �ړ����̃��f����]���x
	float HitRadius = 3.0f;		// �����蔻�蔼�a
	float HitHeight = 16.5f;	// �����蔻�荂��
	VECTOR InitPos = { 0.0f,0.0f,0.0f };	// �������W
};

// �A�j���[�V�����ԍ�
enum class PlayerAnimState :int
{
	None = -1,      // �Ȃ�
	TPose = 0,      // �s��
	Idle = 1,       // �A�C�h��
	Walk = 2,       // ����
	Run = 3,        // ����
	RunPose = 4,    // �_�b�V���|�[�Y
	RunStop = 6,    // �X�g�b�v
	Jump = 7,       // �W�����v
	Fall = 8,       // ������
	Attack1 = 9,		// �ʏ�U���i1�i�K�j
	Attack2 = 10,	// �ʏ�U���i2�i�K�j
	Attack3 = 11,	// �ʏ�U���i3�i�K�j
	AttackDash = 12,	// ����U��
};

class PayerStateBase;
class Player :public Character
{
public:
	Player(const std::string& name) : Character(name){}

	void Init() override;
	void Load() override;
	void Update() override;
	void Draw() override;

	void ChangeState(std::shared_ptr<PlayerStateBase> a_spState);

	// �t���O�Z�b�^�[
	void SetRunFlag(bool flag) { isRunning = flag; }
	void SetMoveFrag(bool flag) { isMove = flag; }
	void SetAttackFrag(bool flag) { isAttack = flag; }

	const bool GetIsAttack()const { return isAttack; }

	const float GetHitRadius() const override { return params.HitRadius; }
	const float GetHitHeight() const override { return params.HitHeight; }

	const MATRIX GetHandMatrix()const { return handMatrix; }

	void OnHitRoof() override;       // �V��ɓ���������
	void OnHitFloor() override;      // ���ɓ���������
	void OnFall() override;          // �������m�肵���Ƃ�

	VECTOR GetMoveInput();		// �X�e�B�b�N�ɂ��ړ��x�N�g���̎擾
	const VECTOR GetTargetMoveDirection() const { return targetMoveDirection; }	// ���f���������ׂ��������擾

	Animation animation;		// �A�j���[�V����
	const PlayerParams GetParams() const { return params; }

private:
	StateMachine stateMachine;	// �X�e�[�g�}�V��
	PlayerParams params;		// �p�����[�^

	MATRIX handMatrix;

	int handBoneIndex = -1;		// ��̃{�[���̔ԍ�

	bool isRunning = false;		// �����Ă��邩
	bool isAttack = false;		// �U������

	void Move();	// ���f���̈ړ�
	void CulcMoveSpeed();	// �ړ����x�̌v�Z

	void UpdateAngle();			// ���f���̊p�x�X�V

};