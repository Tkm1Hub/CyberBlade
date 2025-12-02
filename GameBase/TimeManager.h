#pragma once
class TimeManager
{
private:
	// コンストラクタを非公開にする
	TimeManager() {}

	// コピーコンストラクタと代入演算子を削除
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	
	~TimeManager(){}

public:
	// インスタンスを取得
	static TimeManager& GetInstance()
	{
		static TimeManager instance;
		return instance;
	}

	void Update();

	const float GetTimeScale() { return timeScale; }
	void SetTimeScale(float scale) { timeScale = scale; }

private:
	long long prevTime = 0;
	float deltaTime = 0.0f;       // 実時間
	float scaledDeltaTime = 0.0f; // スロー適用後
	float timeScale = 1.0f;
};