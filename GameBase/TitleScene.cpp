#include "stdafx.h"
#include "TitleScene.h"
#include "Animation.h"
#include "Input.h"

TitleScene::TitleScene(SceneManager& manager)
	: Scene(manager)
{
}

TitleScene::~TitleScene(){}

void TitleScene::Init()
{
	titleHandle = LoadGraph("data/picture/CyberBlade.png");
	titleBackHandle = LoadGraph("data/picture/Title_Back.png");
	player_ModelHandle = MV1LoadModel("data/model/character/Hideron_Title.mv1");
	sword_ModelHandle = MV1LoadModel("data/model/item/Heat-KatanaV2_Title.mv1");
	movie_Handle = LoadGraph("data/movie/TitleMovie.mp4");
	PlayMovieToGraph(movie_Handle);

	swordModelRot.y = DX_PI_F / 2;

	MV1SetPosition(player_ModelHandle, playerModelPos);
	MV1SetScale(player_ModelHandle, playerModelScale);

	MV1SetPosition(sword_ModelHandle, swordModelPos);
	MV1SetScale(sword_ModelHandle, swordModelScale);

	animation = std::make_shared<Animation>();

	animation->LoadAnimation(player_ModelHandle);
	animation->Play(0, false);

	// フォントハンドルの作成
	fontHandle = CreateFontToHandle("源暎ラテゴ v2", 50, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	SetCameraNearFar(0.1f, 2500);
	// カメラを正射影に変更
	SetupCamera_Ortho(2500);

	// ライトの方向指定
	SetLightDirection(lightDir);
}

void TitleScene::Update()
{
	// 入力の更新
	Input::GetInput().Update();

	float distance = TITLE_Y_MAX - title_y;

	if (distance > 0.0f)
	{
		title_y += distance * 0.03f;
	}

	if (title_alpha < 255)
	{
		title_alpha += 2;
	}

	title_alpha = min(title_alpha, 255);

	if (string_alpha > 255 || string_alpha < 40)
	{
		ALPHA_SPEED *= -1;
	}

	string_alpha += 1 * ALPHA_SPEED;

	int input = 0;
	input = Input::GetInput().GetNowFrameNewInput();

	if (16 <= input)
	{
		isChangeScene = true;
	}

	if (isChangeScene)
	{
		fade += 5;
		fade = min(fade, 255);
	}

	if (fade >= 255)
	{
		// ゲームシーンに移行
		ChangeScene("Game");
		SetupCamera_Perspective(60 * DX_PI_F / 180.0f);

		// フォントハンドルを削除
		DeleteFontToHandle(fontHandle);
	}


	SetLightDirection(lightDir);
	SetLightPosition(lightPos);

	MV1SetPosition(player_ModelHandle, playerModelPos);
	MV1SetPosition(sword_ModelHandle, swordModelPos);
	MV1SetRotationXYZ(sword_ModelHandle, swordModelRot);
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 20.0f, 0.0f), VGet(0.0f, 20.0f, 10.0f));
}

void TitleScene::Draw() const
{
	clsDx();

	DrawExtendGraph(0, 0, 670, 1080, titleBackHandle, TRUE);
	MV1DrawModel(player_ModelHandle);
	DrawGraph(movie_x, 0, movie_Handle, TRUE);
	MV1DrawModel(sword_ModelHandle);

	//タイトルロゴ描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_alpha);
	DrawExtendGraph(TITLE_X_OFFSET, title_y - TITLE_HEIGHT, TITLE_X_OFFSET + TITLE_WIDTH, title_y, titleHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, string_alpha);
	DrawFormatStringToHandle(stringPos_x, stringPos_y, GetColor(200, 200, 200),fontHandle, "Press.Start");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawBox(0, 0, 1920, 1080, GetColor(255, 255,255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	printfDx("nowFrameInput : %i", Input::GetInput().GetNowFrameInput());
}