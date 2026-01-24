#include "stdafx.h"
#include "Pause.h"
#include "TimeManager.h"
#include "Input.h"

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
	DeleteGraph(gaussianScreen);
}