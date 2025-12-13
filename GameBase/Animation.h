#pragma once
class Animation
{
public:
    void LoadAnimation(int mHandle);
    void Play(int animIndex,bool loop);
    void Update();
    void SetBlendRate(float newBrendRate) { animBlendRate = newBrendRate; }
    bool GetIsAnimFinished() const { return isAnimFinished; }

    float GetCurrentAnimCount() const { return currentAnimCount; }

    float GetCurrentAnimTotalTime()const { return MV1GetAnimTotalTime(modelHandle, currentPlayAnim); }

    int GetCurrentAnimNum() const { return currentAnimNum; }
private:
    int modelHandle;
    int currentAnimNum = -1;
    int currentPlayAnim = -1;
    int prevPlayAnim = -1;
    float currentAnimCount = 0.0f;
    float prevAnimCount = 0.0f;
    float animBlendRate = 1.0f;
    static constexpr float ANIM_PLAY_SPEED = 0.25f;  // アニメーションの再生速度
    static constexpr float ANIM_BLEND_SPEED = 0.1f; // アニメーションのブレンド率変化速度

    bool isLoop = false;            // ループ再生するか
    bool isAnimFinished = false;    // 再生が終わったか
};