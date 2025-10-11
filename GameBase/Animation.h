#pragma once
class Animation
{
public:
    void LoadAnimation(int mHandle);
    void Play(int animIndex);
    void Update();
    void SetBlendRate(float newBrendRate) { animBlendRate = newBrendRate; }

private:
    int modelHandle;
    int currentPlayAnim = -1;
    int prevPlayAnim = -1;
    float currentAnimCount = 0.0f;
    float prevAnimCount = 0.0f;
    float animBlendRate = 1.0f;
    static constexpr float ANIM_PLAY_SPEED = 0.4f;  // �A�j���[�V�����̍Đ����x
    static constexpr float ANIM_BLEND_SPEED = 0.1f; // �A�j���[�V�����̃u�����h���ω����x
};