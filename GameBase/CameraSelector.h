#pragma once
#include "VirtualCameraBase.h"

class IGameObject;
class MainCamera;
class FreeCamera;

class CameraSelector
{
public:
	CameraSelector(std::shared_ptr<std::vector<std::shared_ptr<VirtualCameraBase>>> list)
		: cameraList(list) {
	}

	void SetCurrentIndex(int idx) { currentIndex = idx; }

	void Update(std::shared_ptr<MainCamera>& mainCamera);

private:
	int currentIndex = 1;
	std::shared_ptr<std::vector<std::shared_ptr<VirtualCameraBase>>> cameraList;
};