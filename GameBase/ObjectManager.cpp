#include "stdafx.h"
#include "ObjectManager.h"
#include "MainCamera.h"
#include "FreeCamera.h"
#include "SkyDome.h"
#include "Stage.h"
#include "Player.h"
#include "Sword.h"
#include "EnemySmall.h"
#include "CheckPoint.h"
void ObjectManager::Create()
{
	skyDome = std::make_shared<SkyDome>("SkyDome");
	stage = std::make_shared<Stage>("Stage");
	player = std::make_shared<Player>("Player");
	sword = std::make_shared<Sword>("Sword");
	enemySmall = std::make_shared<EnemySmall>("EnemySmall");
	checkPoint = std::make_shared<CheckPoint>("CheckPoint");


	sword->SetOwner(player);
	skyDome->SetOwner(player);

	AddObject(skyDome);
	AddObject(stage);
	AddObject(player);
	AddObject(sword);
	AddObject(enemySmall);
	AddObject(checkPoint);
}

void ObjectManager::AddObject(std::shared_ptr<IGameObject> obj)
{
	objects.push_back(obj);
}

/// <summary>
/// オブジェクトを名前で検索する
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
std::shared_ptr<IGameObject> ObjectManager::FindObject(std::string name)
{
	for (auto obj : objects) {
		if (obj->GetName() == name) {
			return obj;
		}
	}
	return nullptr;
}

/// <summary>
/// オブジェクトの初期化
/// </summary>
void ObjectManager::InitAll()
{
	for (auto obj : objects)
	{
		obj->Init();
	}
}

/// <summary>
/// モデルなどのロード
/// </summary>
void ObjectManager::LoadAll()
{
	for (auto obj : objects)
	{
		obj->Load();
	}
}

/// <summary>
/// オブジェクトの更新
/// </summary>
void ObjectManager::UpdateAll()
{
	for (auto obj : objects)
	{
		obj->Update();
	}
}


void ObjectManager::ApplyCollision()
{
	for (auto obj : objects)
	{
		if (obj->GetIsCollisionEnabled())
		{
			obj->SetPosition(obj->GetNextPosition());
			MV1SetPosition(obj->GetModelHandle(), obj->GetPosition());

			if (obj->GetName() == "Player")
			{
				printf("PlayerPos [ %.2f,%.2f,%.2f ] \n", obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);

			}
		}
	}
}

/// <summary>
/// オブジェクトの描画
/// </summary>
void ObjectManager::DrawAll()
{
	for (auto obj : objects)
	{
		obj->Draw();
	}
}