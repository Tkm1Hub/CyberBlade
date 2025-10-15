#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemyBase.h"

void EnemyManager::AddEnemy(std::shared_ptr<EnemyBase> enemy,const VECTOR& initPos) 
{
    enemies.push_back(enemy);
    enemy->SetPosition(initPos);
}

void EnemyManager::Init() {
    for (auto& e : enemies) e->Init();
}

void EnemyManager::Load()
{
    for (auto& e : enemies) e->Load();
}

void EnemyManager::Update() {
    for (auto& e : enemies) e->Update();
}

void EnemyManager::Draw() {
    for (auto& e : enemies) e->Draw();
}

void EnemyManager::ApplyCollision() {
    for (auto& e : enemies) {
        if (e->GetIsCollisionEnabled()) {
            e->SetPosition(e->GetNextPosition());
            MV1SetPosition(e->GetModelHandle(), e->GetPosition());
        }
    }
}

void EnemyManager::RemoveDeadEnemies()
{
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::shared_ptr<EnemyBase>& enemy) {
                return enemy->GetIsDead();  // true‚È‚çíœ
            }),
        enemies.end());
}