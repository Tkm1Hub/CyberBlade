#include "stdafx.h"
#include "GameOver.h"
#include "TimeManager.h"
#include "Input.h"
#include "Sound.h"

void GameOver::Init()
{
	choiceNum = 0;				// 選択中のカーソル番号
	prevTimeScale = 0.0f;		// タイムスケールを保存
	isGameOver = false;

	noiseAlpha = 0;
	textAlpha = 0;

	isChangeScene = false;

	noiseHandle = LoadGraph("data/picture/Noise.png");
	textHandle1 = LoadGraph("data/picture/GameOver_1.png");
	textHandle2 = LoadGraph("data/picture/GameOver_2.png");
}

void GameOver::Update()
{
	if (isGameOver)
	{
		if (noiseAlpha < 255)
		{
			noiseAlpha += fadeSpeed;
			noiseAlpha = min(noiseAlpha, 255);
		}
		else
		{
			if (textAlpha < 255)
			{
				textAlpha += fadeSpeed;
				textAlpha = min(textAlpha, 255);
			}
			else
			{
				if (!isChangeScene)
				{
					Choice();
				}

				if (Input::GetInput().GetNowFrameNewInput() == 64)
				{
					isChangeScene = true;
				}
			}
		}
	}
}

void GameOver::Choice()
{
	if (Input::GetInput().GetNowFrameNewInput() == 8)
	{
		choiceNum--;
		choiceNum = max(choiceNum, 0);
		SoundManager::GetInstance().Play_Sound("カーソル移動");
	}
	else if (Input::GetInput().GetNowFrameNewInput() == 1)
	{
		choiceNum++;
		choiceNum = min(choiceNum, 1);
		SoundManager::GetInstance().Play_Sound("カーソル移動");
	}
}

void GameOver::Draw()
{
	if (!isGameOver)return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, noiseAlpha);
	DrawGraph(0, 0, noiseHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, textAlpha);

	if (choiceNum == 0)
	{
		DrawGraph(0, 0, textHandle1, TRUE);
	}
	else
	{
		DrawGraph(0, 0, textHandle2, TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameOver::StartGameOver()
{
	//prevTimeScale = TimeManager::GetInstance().GetTimeScale();
	//TimeManager::GetInstance().SetTimeScale(0.0f);
	isGameOver = true;
}