#pragma once
struct DamageInstance
{
	int damageNum = -1;
	VECTOR pos;
	bool isActive = false;
	float alpha = 0.0f;
};

class DamageManager
{
private:
    // コンストラクタを非公開にする
    DamageManager() {}

    // コピーコンストラクタと代入演算子を削除
    DamageManager(const DamageManager&) = delete;
    DamageManager& operator=(const DamageManager&) = delete;

    ~DamageManager() {}

    VECTOR position = { 0.0f,0.0f,0.0f };
    int time = 0;
    int fontHandle = -1;
    std::unordered_map<std::string, int> effectHandles;
    std::vector<DamageInstance> activeDamageNum;

public:
    // インスタンスを取得
    static DamageManager& GetInstance()
    {
        static DamageManager instance;
        return instance;
    }

    void Init();
    void Update();
    void Draw();
};
