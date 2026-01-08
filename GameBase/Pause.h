#pragma once

class Pause
{
public:

private:
	int choiceNum = 0;				// 選択中のカーソル番号
	float prevTimeScale = 0.0f;		// タイムスケールを保存

	static constexpr int RESUME = 0;			// ゲームに戻る
	static constexpr int HELP = 1;				// 操作方法
	static constexpr int RETURN_TO_TITLE = 2;	// タイトルに戻る
	static constexpr int EXIT_GAME = 3;			// ゲームをやめる
};