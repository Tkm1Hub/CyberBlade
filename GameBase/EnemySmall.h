#pragma once
#include "EnemyBase.h"
#include "StateMachine.h"

// �p�����[�^
struct EnemySmall_Params
{
	float Gravity = 0.08f;		// �d��
	float DamageSpeed = 1.5f;	// �_���[�W���m�b�N�o�b�N�̑��x
	float HitRadius = 4.0f;		// �����蔻�蔼�a
	float HitHeight = 14.0f;	// �����蔻�荂��
	VECTOR InitPos = { 0.0f,0.0f,30.0f };	// �������W
};

class EnemySmallStateBase;
class EnemySmall :public EnemyBase
{
public:
	EnemySmall(const std::string& name):EnemyBase(name){}

	void Init() override;
	void Load() override;
	void Update() override;

	void SetDamageFlag(bool flag) { isDamage = flag; }
	const bool GetDamageFlag() const { return isDamage; }

	void ChangeState(std::shared_ptr<EnemySmallStateBase> a_spState);

	VECTOR GetKnockBackDir()const { return knockBackDir; }
	void SetKnockBackDir(const VECTOR& direction) { knockBackDir = direction; }

	const float GetHitRadius() const override { return params.HitRadius; }
	const float GetHitHeight() const override { return params.HitHeight; }

	void OnHitRoof() override;       // �V��ɓ���������
	void OnHitFloor() override;      // ���ɓ���������
	void OnFall() override;          // �������m�肵���Ƃ�

	const EnemySmall_Params GetParams() const { return params; }
private:
	EnemySmall_Params params;	// �p�����[�^
	StateMachine stateMachine;	// �X�e�[�g�}�V��

	VECTOR knockBackDir = { 0.0f,0.0f,0.0f };

	bool isDamage = false;

};