#include "stdafx.h"
#include "GameScene.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "CameraManager.h"
#include "Input.h"
#include "ShadowManager.h"
#include "Debug.h"
GameScene::GameScene(SceneManager& manager)
	: Scene{manager}{
	Init();
}

GameScene::~GameScene() {}

void GameScene::Init()
{
	//インスタンス化
	objectMgr = std::make_shared<ObjectManager>();
	collisionMgr = std::make_shared<CollisionManager>();
	shadowMgr = std::make_shared<ShadowManager>();
	debug = std::make_shared<Debug>();

	// オブジェクトの生成
	objectMgr->Create();

	// shared_ptr -> weak_ptr に変換
	std::vector<std::weak_ptr<IGameObject>> weakObjects;
	for (auto& obj : objectMgr->GetObjects()) {
		weakObjects.push_back(obj);
	}

	// カメラマネージャーにオブジェのリストを渡す
	CameraManager::GetCameraManager().SetObjects(weakObjects);
	CameraManager::GetCameraManager().Create();

	// オブジェクトの初期化
	objectMgr->InitAll();
	objectMgr->LoadAll();

	collisionMgr->SetObjects(objectMgr->GetObjects());
	collisionMgr->Init();

	debug->SetObjects(objectMgr->GetObjects());

	shadowMgr->Init();
}

void GameScene::Update()
{
	// 入力の更新
	Input::GetInput().Update();

	// オブジェクトの更新
	objectMgr->UpdateAll();

	// 当たり判定の更新
	collisionMgr->Update();

	// オブジェクトの位置を確定
	objectMgr->ApplyCollision();

	// 影の描画範囲を更新
	auto player = objectMgr->FindObject("Player");
	shadowMgr->Update(player->GetPosition());

	// カメラの更新
	CameraManager::GetCameraManager().Update();

	// デバッグの更新
	debug->Update();
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

	//シャドウマップへの描画を終了
	ShadowMap_DrawEnd();

	// 描画に使用するシャドウマップを設定
	SetUseShadowMap(0, shadowMgr->GetShadowMapHandle());

	// オブジェクトの描画
	objectMgr->DrawAll();

	// デバッグ情報の描画
	debug->Draw();

	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);
}