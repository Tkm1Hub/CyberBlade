#pragma once
#include <iostream>
#include "StateBase.h"
class StateMachine
{
public:
	// �X�e�[�g��ύX����
	void ChangeState(std::shared_ptr<StateBase> newState)
	{
		// ���łɃX�e�[�g���Z�b�g����Ă�����I��
		if (nowState != nullptr)
		{
			nowState->OnExit();
			nowState = nullptr;
		}

		// �V�����X�e�[�g���Z�b�g����
		nowState = newState;

		// �V�����X�e�[�g���J�n����
		nowState->OnStart();
	}

	// �X�V�֐�
	void Update()
	{
		if (nowState != nullptr)
		{
			nowState->OnUpdate();
		}
	}

private:
	std::shared_ptr<StateBase> nowState = nullptr;
};