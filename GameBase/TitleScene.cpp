#include "stdafx.h"
#include "TitleScene.h"
#include "Animation.h"

TitleScene::TitleScene(SceneManager& manager)
	: Scene(manager)
{
}

TitleScene::~TitleScene(){}

void TitleScene::Init()
{
	titleHandle = LoadGraph("data/picture/CyberBlade.png");
	titleBackHandle = LoadGraph("data/picture/Title_Back.png");
	player_ModelHandle = MV1LoadModel("data/model/character/Hideron.mv1");
	MV1SetPosition(player_ModelHandle, playerModelPos);
	MV1SetScale(player_ModelHandle, playerModelScale);


	SetCameraNearFar(0.1f, 500.0f);
	// カメラを正射影に変更
	SetupCamera_Ortho(1000);
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		playerModelPos.x += 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		playerModelPos.x -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		playerModelPos.z -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		playerModelPos.z += 1.0f;
	}


	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		// ゲームシーンに移行
		ChangeScene("Game");
	}

	MV1SetPosition(player_ModelHandle, playerModelPos);
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, 20.0f, 10.0f));
}

void TitleScene::Draw() const
{
	//DrawExtendGraph(0, 0, 670, 1080, titleBackHandle, TRUE);
	MV1DrawModel(player_ModelHandle);
	//DrawExtendGraph(TITLE_X1, TITLE_Y1, TITLE_X2, TITLE_Y2, titleHandle, TRUE);
	//DrawFormatString(600, 400, GetColor(255, 255, 255), "Press.Start");

	clsDx();

	printfDx("pos[x,y,z] : [%.2f,%.2f,%.2f]\n", playerModelPos.x, playerModelPos.y, playerModelPos.z);

	//DrawLine(0, 540, 1920, 540, GetColor(150, 150, 150));
	//DrawLine(960, 0, 960, 1080, GetColor(150, 150, 150));
}