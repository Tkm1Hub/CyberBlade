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
	//�C���X�^���X��
	objectMgr = std::make_shared<ObjectManager>();
	collisionMgr = std::make_shared<CollisionManager>();
	shadowMgr = std::make_shared<ShadowManager>();
	debug = std::make_shared<Debug>();

	// �I�u�W�F�N�g�̐���
	objectMgr->Create();

	// shared_ptr -> weak_ptr �ɕϊ�
	std::vector<std::weak_ptr<IGameObject>> weakObjects;
	for (auto& obj : objectMgr->GetObjects()) {
		weakObjects.push_back(obj);
	}

	// �J�����}�l�[�W���[�ɃI�u�W�F�̃��X�g��n��
	CameraManager::GetCameraManager().SetObjects(weakObjects);
	CameraManager::GetCameraManager().Create();

	// �I�u�W�F�N�g�̏�����
	objectMgr->InitAll();
	objectMgr->LoadAll();

	collisionMgr->SetObjects(objectMgr->GetObjects());
	collisionMgr->Init();

	debug->SetObjects(objectMgr->GetObjects());

	shadowMgr->Init();
}

void GameScene::Update()
{
	// ���͂̍X�V
	Input::GetInput().Update();

	// �I�u�W�F�N�g�̍X�V
	objectMgr->UpdateAll();

	// �����蔻��̍X�V
	collisionMgr->Update();

	// �I�u�W�F�N�g�̈ʒu���m��
	objectMgr->ApplyCollision();

	// �e�̕`��͈͂��X�V
	auto player = objectMgr->FindObject("Player");
	shadowMgr->Update(player->GetPosition());

	// �J�����̍X�V
	CameraManager::GetCameraManager().Update();

	// �f�o�b�O�̍X�V
	debug->Update();
}

void GameScene::Draw()const
{
	//�V���h�E�}�b�v�̏���
	ShadowMap_DrawSetup(shadowMgr->GetShadowMapHandle());

	// �e���L���ȃI�u�W�F�N�g��`��
	for (auto obj : objectMgr->GetObjects())
	{
		if (obj->GetIsShadowEnebled())
		{
			obj->Draw();
		}
	}

	//�V���h�E�}�b�v�ւ̕`����I��
	ShadowMap_DrawEnd();

	// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	SetUseShadowMap(0, shadowMgr->GetShadowMapHandle());

	// �I�u�W�F�N�g�̕`��
	objectMgr->DrawAll();

	// �f�o�b�O���̕`��
	debug->Draw();

	// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
	SetUseShadowMap(0, -1);
}