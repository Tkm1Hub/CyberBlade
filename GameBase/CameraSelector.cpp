#include "stdafx.h"
#include "CameraSelector.h"
#include "FreeCamera.h"
#include "MainCamera.h"

void CameraSelector::Update(std::shared_ptr<MainCamera>& mainCamera)
{
    if (!cameraList) {
        // cameraListがnullptrの場合、ここで警告メッセージを出す
        std::cerr << "cameraList is nullptr!" << std::endl;
        return;
    }

    if (cameraList->empty()) {
        // cameraListが空の場合、ここで警告メッセージを出す
        std::cerr << "cameraList is empty!" << std::endl;
        return;
    }

    // 入力でカメラ切り替え（例：1キー〜2キー）
    if (CheckHitKey(KEY_INPUT_1)) currentIndex =2;
    if (CheckHitKey(KEY_INPUT_2)) currentIndex = 3;

	auto& currentCam = (*cameraList)[currentIndex];

	VECTOR nextPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR nextTarget = VGet(0.0f, 0.0f, 0.0f);

	nextPos = currentCam->GetPosition();
	nextTarget = currentCam->GetTarget();

	mainCamera->SetCameraPositionAndTarget(nextPos, nextTarget);
	
}