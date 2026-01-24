#pragma once

class Pause
{
private:
	// コンストラクタを非公開にする
	Pause() {}

	// コピーコンストラクタと代入演算子を削除
	Pause(const Pause&) = delete;
	Pause& operator=(const Pause&) = delete;

	~Pause() {}
public:
	// インスタンスを取得
	static Pause& GetInstance()
	{
		static Pause instance;
		return instance;
	}

	void StartPause();	// ポーズ開始
	void EndPause();	// ポーズ終了
	
	int GetScreenHandle() const { return gaussianScreen; }

	bool GetIsPause() const { return isPause; }

private:
	int gaussianScreen = -1;		// スクリーンハンドル
	int choiceNum = 0;				// 選択中のカーソル番号
	float prevTimeScale = 0.0f;		// タイムスケールを保存
	bool isPause = false;

	static constexpr int RESUME = 0;			// ゲームに戻る
	static constexpr int RETURN_TO_TITLE = 1;	// タイトルに戻る
	static constexpr int EXIT_GAME = 2;			// ゲームをやめる
};