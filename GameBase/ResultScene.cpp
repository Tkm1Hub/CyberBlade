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
	player_ModelHandle = MV1LoadModel("data/model/character/Hideron_Title.mv1");

	MV1SetPosition(player_ModelHandle, playerModelPos);
	MV1SetScale(player_ModelHandle, playerModelScale);

	animation = std::make_shared<Animation>();

	animation->LoadAnimation(player_ModelHandle);
	animation->Play(2, true);

	SetCameraNearFar(0.1f, 2500);

	// カメラを正射影に変更
	SetupCamera_Ortho(2500);

	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, 20.0f, 10.0f));
}

void ResultScene::Update()
{
	// 入力の更新
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

	if (CheckHitKey(KEY_INPUT_UP))
	{
		playerModelScale = VAdd(playerModelScale, VGet(1.0f, 1.0f, 1.0f));
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		playerModelScale = VSub(playerModelScale, VGet(1.0f, 1.0f, 1.0f));
	}


	if (isChangeScene && fade == 255)
	{
		ChangeScene("Title");
	}

	animation->Update();

	MV1SetPosition(player_ModelHandle, playerModelPos);

}

void ResultScene::Draw() const
{
	clsDx();

	printfDx("A : Back To Title");

	DrawGraph(0, 0, imgHandle, TRUE);

	MV1DrawModel(player_ModelHandle);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawBox(0, 0, 1920, 1080, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}