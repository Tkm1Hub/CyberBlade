#include "stdafx.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "MainCamera.h"
#include "FreeCamera.h"
#include "SkyDome.h"
#include "Stage.h"
#include "Player.h"
#include "Sword.h"
#include "EnemySmall.h"
#include "EnemyBig.h"
#include "CheckPoint.h"
#include "UIManager.h"
void ObjectManager::Create()
{
	// 二重作成を防ぐ
	if (!objects.empty())
	{
		return;
	}

	skyDome = std::make_shared<SkyDome>("SkyDome");
	stage = std::make_shared<Stage>("Stage");
	player = std::make_shared<Player>("Player");
	sword = std::make_shared<Sword>("Sword");
	checkPoint = std::make_shared<CheckPoint>("CheckPoint1");

	sword->SetOwner(player);
	skyDome->SetOwner(player);

	// オブジェクトリストに追加
	AddObject(player);
	AddObject(skyDome);
	AddObject(stage);
	AddObject(sword);
	AddObject(checkPoint);

	// 敵の生成
	auto Enemy1 = std::make_shared<EnemySmall>("EnemySmall1");
	auto Enemy2 = std::make_shared<EnemySmall>("EnemySmall2");
	auto Enemy3 = std::make_shared<EnemySmall>("EnemySmall3");
	auto Enemy4 = std::make_shared<EnemySmall>("EnemySmall4");

	auto EnemyBoss = std::make_shared<EnemyBig>("EnemyBoss");
	UIManager::GetUIManager().SetBoss(EnemyBoss);

	EnemyManager::GetEnemyManager().AddEnemy(Enemy1, VGet(0, 0, 70));
	//EnemyManager::GetEnemyManager().AddEnemy(Enemy2, VGet(0, 0, 50));
	//EnemyManager::GetEnemyManager().AddEnemy(Enemy3, VGet(0, 0, 0));
	//EnemyManager::GetEnemyManager().AddEnemy(Enemy4, VGet(0, 0, 30));
	EnemyManager::GetEnemyManager().AddEnemy(EnemyBoss, VGet(1406, 16, 168));

	// UI表示オブジェクトをリストに追加
	AddUIDisplayTarget(Enemy1);
	AddUIDisplayTarget(Enemy2);
	AddUIDisplayTarget(Enemy3);
	AddUIDisplayTarget(Enemy4);
	AddUIDisplayTarget(EnemyBoss);

}

void ObjectManager::AddObject(std::shared_ptr<IGameObject> obj)
{
	objects.push_back(obj);
}

void ObjectManager::AddUIDisplayTarget(std::shared_ptr<IGameObject> obj)
{
	uiDisplayTargets.push_back(obj);
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

	EnemyManager::GetEnemyManager().Init();
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

	EnemyManager::GetEnemyManager().Load();
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

	EnemyManager::GetEnemyManager().Update();

	EnemyManager::GetEnemyManager().RemoveDeadEnemies();
}


void ObjectManager::ApplyCollision()
{
	for (auto obj : objects)
	{
		if (obj->GetIsCollisionEnabled())
		{
			obj->SetPosition(obj->GetNextPosition());
			MV1SetPosition(obj->GetModelHandle(), obj->GetPosition());

		}
	}

	EnemyManager::GetEnemyManager().ApplyCollision();
}

/// <summary>
/// オブジェクトの描画
/// </summary>
void ObjectManager::DrawAll()
{
	bool isDodgeJust = false;

	for (auto obj : objects)
	{

		if (obj->GetName() == "Player")
		{
			auto player = std::dynamic_pointer_cast<Player>(obj);
			isDodgeJust = player->GetIsDodgeJust();
		}
		else
		{
			if (isDodgeJust)
			{
				MV1SetDifColorScale(obj->GetModelHandle(), GetColorF(0.4f, 0.4f, 0.4f, 1.0f));
			}
			else
			{
				MV1SetDifColorScale(obj->GetModelHandle(), GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}

		obj->Draw();
	}

	EnemyManager::GetEnemyManager().Draw();
}