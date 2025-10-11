#include "stdafx.h"
#include "CameraSelector.h"
#include "FreeCamera.h"
#include "MainCamera.h"

void CameraSelector::Update(std::shared_ptr<MainCamera>& mainCamera)
{
    if (!cameraList) {
        // cameraList��nullptr�̏ꍇ�A�����Ōx�����b�Z�[�W���o��
        std::cerr << "cameraList is nullptr!" << std::endl;
        return;
    }

    if (cameraList->empty()) {
        // cameraList����̏ꍇ�A�����Ōx�����b�Z�[�W���o��
        std::cerr << "cameraList is empty!" << std::endl;
        return;
    }

	auto& currentCam = (*cameraList)[currentIndex];

	VECTOR nextPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR nextTarget = VGet(0.0f, 0.0f, 0.0f);

	nextPos = currentCam->GetPosition();
	nextTarget = currentCam->GetTarget();

	mainCamera->SetCameraPositionAndTarget(nextPos, nextTarget);
	
}