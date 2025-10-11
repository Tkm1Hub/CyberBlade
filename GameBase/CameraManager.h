#pragma once
#include "VirtualCameraBase.h"
#include "MainCamera.h"
#include "FreeCamera.h"

class CameraSelector;
class Player;
class CameraManager
{
private:
	// コンストラクタを非公開にする
	CameraManager(){}

	// コピーコンストラクタと代入演算子を削除
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;

	~CameraManager(){}
public:
	// インスタンスを取得するためのメソッド
	static CameraManager& GetCameraManager()
	{
		static CameraManager instance;
		return instance;
	}

	void SetObjects(std::vector<std::weak_ptr<IGameObject>>objectsPtr)
	{
		objects = objectsPtr;
	}
	void Create();
	void Init();
	void AddCamera(std::shared_ptr<VirtualCameraBase> camera);
	void Update();

	std::shared_ptr<MainCamera> GetMainCamera() const { return mainCamera; }
private:
	std::vector<std::weak_ptr<IGameObject>>objects;
	std::shared_ptr<Player> player = nullptr;
	std::vector<std::shared_ptr<VirtualCameraBase>> cameras;
	std::shared_ptr<CameraSelector> cameraSelector = nullptr;
	std::shared_ptr<MainCamera> mainCamera = nullptr;
	std::shared_ptr<FreeCamera> freeCamera = nullptr;
};