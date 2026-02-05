#pragma once

class GameOver
{
private:
	// コンストラクタを非公開にする
	GameOver() {}

	// コピーコンストラクタと代入演算子を削除
	GameOver(const GameOver&) = delete;
	GameOver& operator=(const GameOver&) = delete;

	~GameOver() {}
public:
	// インスタンスを取得
	static GameOver& GetInstance()
	{
		static GameOver instance;
		return instance;
	}

	void Init();		// 初期化
	void Update();		// 更新
	void Choice();		// 選択
	void Draw();		// 描画

	void StartGameOver();	// ゲームオーバー

	bool GetIsGameOver() const { return isGameOver; }

	bool GetIsChengeScene() const { return isChangeScene; }

	int GetChoiceNum() const { return choiceNum; }

private:

	int noiseHandle = -1;				// ノイズ画像ハンドル
	int textHandle1 = -1;				// テキスト画像ハンドル
	int textHandle2 = -1;				// テキスト画像ハンドル
	int choiceNum = 0;				// 選択中のカーソル番号

	int noiseAlpha = -1;			// ノイズ画像の透明度
	int textAlpha = -1;				// テキストの透明度

	int fadeSpeed = 3;

	int BoxWidth = 300;
	int BoxHeight = 60;

	float prevTimeScale = 0.0f;		// タイムスケールを保存
	bool isGameOver = false;

	bool isChangeScene = false;

	static constexpr int RESTART = 0;			// はじめからやり直す
	static constexpr int RETURN_TO_TITLE = 1;	// タイトルに戻る
};