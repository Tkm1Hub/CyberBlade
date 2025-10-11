#include "stdafx.h"
#include "Input.h"

void Input::Update()
{
    //�ЂƂO�̃t���[���̓��͂�ϐ��ɂƂ��Ă���
    int Old = nowFrameInput;
    //���݂̓��͏󋵂��擾
    nowFrameInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    //�X�e�B�b�N�֘A�̐��l�v�Z
    CalcStickInput();

    //���̃t���[���ŐV���ɉ����ꂽ�{�^���̃r�b�g���������Ă���l�� nowFrameNewInput �ɕۑ�����B
    nowFrameNewInput = nowFrameInput & ~Old;
}


/// @brief �X�e�B�b�N�̐��l���v�Z
void Input::CalcStickInput()
{
    int inputX_L = 0;
    int inputY_L = 0;
    int inputX_R = 0;
    int inputY_R = 0;

    leftStickX = 0.0f;
    leftStickY = 0.0f;
    rightStickX = 0.0f;
    rightStickY = 0.0f;


    // ���E�̃X�e�B�b�N�̏�Ԃ��擾
    GetJoypadAnalogInput(&inputX_L, &inputY_L, DX_INPUT_PAD1);
    GetJoypadAnalogInputRight(&inputX_R, &inputY_R, DX_INPUT_PAD1);

    // �f�b�h�]�[���ȏ�̏ꍇfloat�ɕϊ����ĕۑ�
    // ���X�e�B�b�N
    if (fabs(inputX_L) > DEADZONE || fabs(inputY_L) > DEADZONE)
    {
        isMoveLStick = true;

        leftStickX = static_cast<float>(inputX_L);
        leftStickY = static_cast<float>(inputY_L);
    }
    else
    {
        isMoveLStick = false;
    }

    // �E�X�e�B�b�N
    if (fabs(inputX_R) > DEADZONE || fabs(inputY_R) > DEADZONE)
    {
        isMoveRStick = true;

        rightStickX = static_cast<float>(inputX_R);
        rightStickY = static_cast<float>(inputY_R);
    }
    else
    {
        isMoveRStick = false;
    }

    //�X�e�B�b�N�̌X���x�������v�Z
    RStickAngle = fabs(sqrtf(rightStickX * rightStickX + rightStickY * rightStickY));
    LStickAngle = fabs(sqrtf(leftStickX * leftStickX + leftStickY * leftStickY));

}