#include "stdafx.h"
#include "CameraManager.h"
#include "CameraSelector.h"
#include "LockOnCamera.h"
#include "Player.h"

void CameraManager::Create()
{
	// 二重作成を防ぐ
	//if (!cameras.empty())
	//{
	//	printf("CameraManager::Create() が複数回呼ばれました！スキップします。\n");
	//	return;
	//}

	for (auto& objWeak : objects)
	{
		if (auto obj = objWeak.lock())
		{
			auto p = std::dynamic_pointer_cast<Player>(obj);
			if (p)
			{
				player = p;
				break;
			}
		}
	}

	// インスタンス化
	mainCamera = std::make_shared<MainCamera>("MainCamera");
	mainCamera->Init();
	freeCamera = std::make_shared<FreeCamera>("FreeCamera");
	freeCamera->Init();
	freeCamera->SetPlayer(player);
	lockOnCamera = std::make_shared<LockOnCamera>("LockOnCamera");
	lockOnCamera->SetPlayer(player);

	// カメラをリストに追加
	AddCamera(freeCamera);
	AddCamera(lockOnCamera);

	auto cameraList = std::make_shared<std::vector<std::shared_ptr<VirtualCameraBase>>>(cameras);

	cameraSelector = std::make_shared<CameraSelector>(cameraList);
}

void CameraManager::AddCamera(std::shared_ptr<VirtualCameraBase> camera)
{
	// 既に同じカメラが登録済みなら追加しない
	//auto it = std::find(cameras.begin(), cameras.end(), camera);
	//if (it == cameras.end())
	//{
		cameras.push_back(camera);
	//}
}

void CameraManager::Init()
{

}

void CameraManager::Update()
{
	for (auto& cam : cameras)
	{
		cam->Update();
	}

	cameraSelector->Update(mainCamera);
	mainCamera->Update();
}

void CameraManager::ChangeCamera(int cameraIndex)
{
	cameraSelector->SetCurrentIndex(cameraIndex);
}