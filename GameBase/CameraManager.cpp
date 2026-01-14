#include "stdafx.h"
#include "CameraManager.h"
#include "LockOnCamera.h"
#include "Player.h"

void CameraManager::Create()
{

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

	// 初期のカメラはフリーカメラに設定
	currentCamera = freeCamera;

	// バーチャルカメラをリストに追加
	AddCamera(freeCamera);
	AddCamera(lockOnCamera);
}

void CameraManager::AddCamera(std::shared_ptr<VirtualCameraBase> camera)
{
	cameras.push_back(camera);
}

void CameraManager::Init()
{
	objects.clear();
	cameras.clear();

	player.reset();
	mainCamera.reset();
	freeCamera.reset();
	lockOnCamera.reset();
	currentCamera.reset();
}

void CameraManager::Update()
{
	// 選択中のバーチャルカメラを更新
	currentCamera->Update();

	// メインカメラに選択中のカメラの座標を渡す
	mainCamera->SetCameraPositionAndTarget(currentCamera->GetPosition(), currentCamera->GetTarget());

	// メインカメラの更新
	mainCamera->Update();
}

void CameraManager::ChangeCamera(int cameraIndex)
{
	// 現在のカメラを非アクティブ化する
	currentCamera->SetIsActive(false);

	// 水平角度を引き継ぐ
	float currentAngleH = currentCamera->GetAngleH();

	// 現在のカメラを変更してアクティブ化する
	currentCamera = cameras[cameraIndex];
	currentCamera->SetIsActive(true);
	// 変更後、カメラの初期化処理を行う
	currentCamera->Init();
	currentCamera->SetAngleH(currentAngleH);


}