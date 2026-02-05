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

	void Init();		// 初期化
	void Update();		// 更新
	void Choice();		// 選択
	void Draw();		// 描画

	void StartPause();	// ポーズ開始
	void EndPause();	// ポーズ終了
	
	int GetScreenHandle() const { return gaussianScreen; }

	bool GetIsPause() const { return isPause; }
	bool GetIsChangeScene() const { return isChangeScene; }

private:

	int imgHandle1 = -1;				// 画像ハンドル
	int imgHandle2 = -1;				// 画像ハンドル
	int gaussianScreen = -1;		// スクリーンハンドル
	int choiceNum = 0;				// 選択中のカーソル番号
	float prevTimeScale = 0.0f;		// タイムスケールを保存
	bool isPause = false;
	bool isChangeScene = false;

	static constexpr int RESUME = 0;			// ゲームに戻る
	static constexpr int RETURN_TO_TITLE = 1;	// タイトルに戻る
	static constexpr int EXIT_GAME = 2;			// ゲームをやめる
};