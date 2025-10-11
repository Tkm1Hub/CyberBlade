#include "stdafx.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneManager& manager)
	: Scene(manager)
{
}

TitleScene::~TitleScene(){}

void TitleScene::Init()
{

}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		// ゲームシーンに移行
		ChangeScene("Game");
	}
}

void TitleScene::Draw() const
{
	DrawFormatString(600, 400, GetColor(255, 255, 255), "Press ENTER to Start");
}