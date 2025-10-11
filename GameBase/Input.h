#pragma once

//��l�v���C�݂̂̂��߃V���O���g���ō쐬
class Input
{
private:
    //�R���X�g���N�^�����J�ɂ���
    Input() {}

    // �R�s�[�R���X�g���N�^�Ƒ�����Z�q���폜
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    //�v���C�x�[�g�f�X�g���N�^
    ~Input() {}

public:
    // �C���X�^���X���擾���邽�߂̃��\�b�h
    static Input& GetInput()
    {
        static Input instance;      // �ÓI�ϐ��Ƃ��ăC���X�^���X���`
        return instance;
    }

    //�L�[�̎��
    enum KeyKinds
    {
        Move = 0,  //�ړ��L�[�̂ǂꂩ
        Left = 1,  //�E
        Right = 2,  //��
        Up = 3,  //��
        Down = 4,  //��
        Space = 5,  //�X�y�[�X
        LB = 6,  //����̎�O�̃{�^��
        LT = 7,  //����̉����̃{�^��
        RB = 8,  //�E��̎�O�̃{�^��
        RT = 9,  //�E�����̃{�^��
        X = 10,
        Y = 11,
        A = 12,
        B = 13,
        LeftStick = 14,  //���X�e�B�b�N��������
        None = 15,  //�g�p���Ȃ��L�[�������͉�����Ă��Ȃ�
    };

    void Update();

    int GetNowFrameInput() const { return nowFrameInput; }
    int GetNowFrameNewInput() const { return nowFrameNewInput; }

    bool GetIsMoveLStick() const { return isMoveLStick; }
    bool GetIsMoveRStick() const { return isMoveRStick; }

    float GetLeftStickX() const { return leftStickX; }
    float GetLeftStickY() const { return leftStickY; }
    float GetRightStickX() const { return rightStickX; }
    float GetRightStickY() const { return rightStickY; }

    float GetRStickAngle() const { return RStickAngle; }
    float GetLStickAngle() const { return LStickAngle; }
private:
    static constexpr int DEADZONE = 10;     // �X�e�B�b�N��|���Ă������������Ȃ��̈�

    int nowFrameInput = 0;          // ���݂̃t���[���ŉ�����Ă���{�^��
    int nowFrameNewInput = 0;       // ���݂̃t���[���ŐV���ɉ����ꂽ�{�^��
    bool isMoveRStick = false;      // �E�X�e�B�b�N���X���Ă��邩
    bool isMoveLStick = false;      // ���X�e�B�b�N���X���Ă��邩

    float leftStickX = 0.0f;        // ���X�e�B�b�N��X���̌X��
    float leftStickY = 0.0f;        // ���X�e�B�b�N��Y���̌X��
    float rightStickX = 0.0f;       // �E�X�e�B�b�N��X���̌X��
    float rightStickY = 0.0f;       // �E�X�e�B�b�N��Y���̌X��
    float LStickAngle = 0.0f;       // ���X�e�B�b�N�̌X���x
    float RStickAngle = 0.0f;       // �E�X�e�B�b�N�̌X���x

    void CalcStickInput();

};