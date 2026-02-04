#include "stdafx.h"
#include "ResultScene.h"
#include "Animation.h"
#include "Input.h"

ResultScene::ResultScene(SceneManager& manager)
	: Scene(manager)
{
}

ResultScene::~ResultScene() {}

void ResultScene::Init()
{
	isChangeScene = false;
	fade = 255;

	imgHandle = LoadGraph("data/picture/Result.png");
}

void ResultScene::Update()
{
	// “ü—Í‚ÌXV
	Input::GetInput().Update();

	if (!isChangeScene)
	{
		if (Input::GetInput().GetNowFrameNewInput() >= 16)
		{
			isChangeScene = true;
		}
		fade -= 5;
		fade = max(fade, 0);
	}
	else
	{
		fade += 5;
		fade = min(fade, 255);
	}

	if (isChangeScene && fade == 255)
	{
		ChangeScene("Title");
	}
}

void ResultScene::Draw() const
{
	clsDx();

	printfDx("A : Back To Title");

	DrawGraph(0, 0, imgHandle, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawBox(0, 0, 1920, 1080, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}