#include "stdafx.h"
#include "Pause.h"
#include "TimeManager.h"
#include "Input.h"

void Pause::Init()
{
	gaussianScreen = -1;		// スクリーンハンドル
	choiceNum = 0;				// 選択中のカーソル番号
	prevTimeScale = 0.0f;		// タイムスケールを保存
	isPause = false;

	imgHandle = LoadGraph("data/picture/PAUSE.png");
}

void Pause::Update()
{
	if (!isPause)
	{
		if (Input::GetInput().GetNowFrameNewInput() == 32768)
		{
			StartPause();
		}
	}
	else
	{
		Choice();
		if (Input::GetInput().GetNowFrameNewInput() == 64)
		{
			switch (choiceNum)
			{
			case 0:
				EndPause();
				break;
			case 1:

				break;
			case 2:

				break;
			}
		}
		else if (Input::GetInput().GetNowFrameNewInput() == 128)
		{
			EndPause();
		}
	}
}

void Pause::Choice()
{
	if (Input::GetInput().GetNowFrameNewInput() == 64)
	{
		if (Input::GetInput().GetNowFrameNewInput() == 1)
		{
			choiceNum--;
			choiceNum = max(choiceNum, 0);
		}
		else if (Input::GetInput().GetNowFrameNewInput() == 8)
		{
			choiceNum++;
			choiceNum = min(choiceNum, 2);
		}
	}
	else if (Input::GetInput().GetNowFrameNewInput() == 128)
	{

	}
}

void Pause::Draw()
{
	if (!isPause)return;
	DrawGraph(0, 0, gaussianScreen, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
	DrawBox(800, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(0, 0, imgHandle, TRUE);
	printfDx("%i\n", choiceNum);
}

void Pause::StartPause()
{
	prevTimeScale = TimeManager::GetInstance().GetTimeScale();
	TimeManager::GetInstance().SetTimeScale(0.0f);
	isPause = true;
	gaussianScreen = MakeGraph(1920, 1080);
	GetDrawScreenGraph(0, 0, 1920, 1080, gaussianScreen);
	GraphFilter(gaussianScreen, DX_GRAPH_FILTER_GAUSS, 8, 700);
}

void Pause::EndPause()
{
	TimeManager::GetInstance().SetTimeScale(prevTimeScale);
	isPause = false;
	choiceNum = 0;
	DeleteGraph(gaussianScreen);
}