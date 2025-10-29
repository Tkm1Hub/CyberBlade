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

VECTOR EnemyManager::GetNearestEnemyPos(const VECTOR& playerPos)const
{
    VECTOR nearestPos = VGet(0.0f, 0.0f, 0.0f);
    float nearestDist = FLT_MAX;    // ˆê”Ô¬‚³‚¢‹——£‚ð•Û‘¶

    for (const auto& enemy : enemies)
    {
        // –³Œø or Ž€–S‚µ‚½“G‚ÍƒXƒLƒbƒv
        if (!enemy || enemy->GetIsDead()) continue;

        // ƒvƒŒƒCƒ„[‚Æ‚Ì‹——£‚ðŒvŽZ
        float dist = VSize(VSub(enemy->GetPosition(), playerPos));

        // ‚æ‚è‹ß‚¢“G‚ð”­Œ©
        if (dist < nearestDist)
        {
            nearestDist = dist;
            nearestPos = enemy->GetPosition();
        }
    }

    return nearestPos;
}

std::shared_ptr<EnemyBase> EnemyManager::GetNearestEnemy(const VECTOR& playerPos)
{
    std::shared_ptr<EnemyBase> nearestEnemy = nullptr;  // ‰Šú‚Í nullptr
    float nearestDist = FLT_MAX;                        // Å¬‹——£‚ð‰Šú‰»

    for (const auto& enemy : enemies)
    {
        if (!enemy || enemy->GetIsDead()) continue;    // –³Œø‚È“G‚âŽ€‚ñ‚Å‚é“G‚ÍƒXƒLƒbƒv

        float dist = VSize(VSub(enemy->GetPosition(), playerPos));

        if (dist < nearestDist)
        {
            nearestDist = dist;
            nearestEnemy = enemy;  // ˆê”Ô‹ß‚¢“G‚ð•Û‘¶
        }
    }

    return nearestEnemy;  // nullptr ‚©AÅ‚à‹ß‚¢“G‚Ì shared_ptr
}
