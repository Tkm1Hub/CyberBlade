#pragma once
struct SoundInstance
{
    std::string name;
    int handle = -1;
};


class SoundManager
{
private:
    // コンストラクタを非公開にする
    SoundManager() {}

    // コピーコンストラクタと代入演算子を削除
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    ~SoundManager() {}

    VECTOR position = { 0.0f,0.0f,0.0f };
    int time = 0;
    int playingSoundHandle = -1;
    int resourceHandle = -1;
    std::unordered_map<std::string, int> soundHandles;

    int BGM_Title = -1;
    int BGM_Game = -1;

    int SE_Player_Slash = -1;
    int SE_Player_Jump = -1;


public:
    // インスタンスを取得
    static SoundManager& GetInstance()
    {
        static SoundManager instance;
        return instance;
    }

    void Init();
    void LoadSound(const std::string& name, const std::string& path);
    void Play_Sound(const std::string& name, bool isLoop);
    void StopSound(const std::string& name);
};

