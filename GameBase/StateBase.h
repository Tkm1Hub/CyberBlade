#pragma once
class StateBase
{
public:
	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	virtual void OnStart(){}

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	virtual void OnUpdate(){}

	// �X�e�[�g���I������ۂɈ�x�����Ă΂��֐�
	virtual void OnExit(){}
};