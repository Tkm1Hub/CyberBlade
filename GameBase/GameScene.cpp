#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "CameraManager.h"
#include "Input.h"
#include "ShadowManager.h"
#include "EnemyManager.h"
#include "UIManager.h"
#include "Debug.h"
#include "Player.h"
#include "EffectManager.h"
#include "Pause.h"
#include "Sound.h"

GameScene::GameScene(SceneManager& manager)
	: Scene{manager}{
}

GameScene::~GameScene() {}

void GameScene::Init()
{
	EnemyManager::GetEnemyManager().Clear();
	Pause::GetInstance().Init();

	fade = 255;

	// フォントハンドルの作成
	fontHandle = CreateFontToHandle("源暎ラテゴ v2", 50, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	UIHandle = LoadGraph("data/picture/UI.png");

	SoundManager::GetInstance().Play_Sound("BGM_Game", true);

	//インスタンス化
	objectMgr = std::make_shared<ObjectManager>();
	collisionMgr = std::make_shared<CollisionManager>();
	shadowMgr = std::make_shared<ShadowManager>();
	debug = std::make_shared<Debug>();

	// オブジェクトの生成
	objectMgr->Create();

	// オブジェクトの初期化
	objectMgr->InitAll();
	objectMgr->LoadAll();

	auto playerObj = objectMgr->FindObject("Player");

	// IGameObject → Player へキャスト
	auto player = std::dynamic_pointer_cast<Player>(playerObj);

	if (player)
	{
		EnemyManager::GetEnemyManager().SetPlayer(player);
		UIManager::GetUIManager().SetPlayer(player);
	}

	// shared_ptr -> weak_ptr に変換
	std::vector<std::weak_ptr<IGameObject>> weakObjects;
	for (auto& obj : objectMgr->GetObjects()) {
		weakObjects.push_back(obj);
	}

	// カメラマネージャーにオブジェのリストを渡す
	CameraManager::GetCameraManager().Init();
	CameraManager::GetCameraManager().SetPlayer(player);
	CameraManager::GetCameraManager().SetObjects(weakObjects);
	CameraManager::GetCameraManager().Create();


	collisionMgr->SetObjects(objectMgr->GetObjects());
	collisionMgr->SetEnemies(EnemyManager::GetEnemyManager().GetEnemies());
	collisionMgr->Init();

#if defined (_DEBUG)
	debug->SetObjects(objectMgr->GetObjects());
	debug->SetEnemies(EnemyManager::GetEnemyManager().GetEnemies());
#endif

	shadowMgr->Init();

	UIManager::GetUIManager().Init();
	EffectManager::GetInstance().Init();
}

void GameScene::Update()
{
	if (!isChangeScene)
	{
		fade -= 3;
		fade = max(fade, 0);
	}
	else
	{
		fade += 3;
		fade = min(fade, 255);
	}

	// 入力の更新
	Input::GetInput().Update();

	if (!Pause::GetInstance().GetIsPause())
	{
		// オブジェクトの更新
		objectMgr->UpdateAll();

		// カメラの更新
		CameraManager::GetCameraManager().Update();
	}

	Pause::GetInstance().Update();

	// ボスが死亡しているか確認
	isChangeScene = EnemyManager::GetEnemyManager().GetIsBossDead();

	// 当たり判定の更新
	collisionMgr->Update();

	// オブジェクトの位置を確定
	objectMgr->ApplyCollision();

	// 影の描画範囲を更新
	auto player = objectMgr->FindObject("Player");
	shadowMgr->Update(player->GetPosition());

	// UIの更新
	UIManager::GetUIManager().Update();

	// エフェクトの更新
	EffectManager::GetInstance().Update();

#if defined (_DEBUG)
	// デバッグの更新
	debug->Update();
#endif

	if (isChangeScene && fade == 255)
	{
		ChangeScene("Result");
		SoundManager::GetInstance().StopSound("BGM_Game");
	}
}

void GameScene::Draw()const
{
	//シャドウマップの準備
	ShadowMap_DrawSetup(shadowMgr->GetShadowMapHandle());

	// 影が有効なオブジェクトを描画
	for (auto obj : objectMgr->GetObjects())
	{
		if (obj->GetIsShadowEnebled())
		{
			obj->Draw();
		}
	}

	EnemyManager::GetEnemyManager().Draw();

	//シャドウマップへの描画を終了
	ShadowMap_DrawEnd();

	// 描画に使用するシャドウマップを設定
	SetUseShadowMap(0, shadowMgr->GetShadowMapHandle());

	// オブジェクトの描画
	objectMgr->DrawAll();

	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);

	// デバッグ情報の描画
	debug->Draw();

	// エフェクトの描画
	EffectManager::GetInstance().Draw();
	
	DrawGraph(0, 0, UIHandle, TRUE);

	// UIの描画
	UIManager::GetUIManager().Draw();

	Pause::GetInstance().Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawBox(0, 0, 1920, 1080, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}