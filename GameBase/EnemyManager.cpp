#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemySmall.h"

void EnemyManager::Init()
{
	for (int i = 0; i < ENEMY_NUM + 1; i++)
	{
		enemys.push_back(std::make_shared<Character>());
	}
}

void EnemyManager::Update()
{
	for (auto& enemy : enemys)
	{
		
	}
}