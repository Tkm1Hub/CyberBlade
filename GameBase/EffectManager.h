#pragma once
struct EffectInstance
{
    int handle = -1;
    VECTOR position;
    bool isPlaying = false;
};


class EffectManager
{
private:
    // コンストラクタを非公開にする
    EffectManager(){}

    // コピーコンストラクタと代入演算子を削除
    EffectManager(const EffectManager&) = delete;
    EffectManager& operator=(const EffectManager&) = delete;

    ~EffectManager(){}

    VECTOR position = { 0.0f,0.0f,0.0f };
    int time = 0;
    int playingEffectHandle = -1;
    int resourceHandle = -1;
    std::unordered_map<std::string, int> effectHandles;
    std::vector<EffectInstance> activeEffects;

public:
    // インスタンスを取得
    static EffectManager& GetInstance()
    {
        static EffectManager instance;
        return instance;
    }

    void Init();
    void LoadEffect(const std::string& name, const std::string& path, float magnification);
    void PositionUpdate(const VECTOR& objectPosition);
    void Update();
    void Draw();
    void SetPosition(const VECTOR setPosition);
    void SetRotation(VECTOR setPosition);
    void SetScale(VECTOR scale);
    void SetSpeed(float speed);
    void PlayEffect(const std::string& name, const VECTOR& position);
    void StopEffect();
};

