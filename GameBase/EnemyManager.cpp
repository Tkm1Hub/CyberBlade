#include "stdafx.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "UIManager.h"
#include "HPBar_Enemy.h"

void EnemyManager::AddEnemy(std::shared_ptr<EnemyBase> enemy, const VECTOR& initPos)
{
    enemies.push_back(enemy);
    enemy->SetPosition(initPos);
    // HPƒo[‚Ì¶¬
    auto hpBar = std::make_shared<HPBar_Enemy>();
    hpBar->Init();
    hpBar->SetEnemy(enemy);
    UIManager::GetUIManager().AddUI(hpBar);

    // ƒvƒŒƒCƒ„[‚ª“o˜^Ï‚İ‚È‚ç‘¦ƒZƒbƒg
    if (auto p = m_pPlayer.lock())
    {
        enemy->SetPlayer(p);
    }

}

void EnemyManager::SetPlayer(const std::shared_ptr<Player>& player)
{
    m_pPlayer = player;

    // ‚·‚Å‚É¶¬Ï‚İ‚Ì“G‚É‚à‚Ü‚Æ‚ß‚ÄƒZƒbƒg
    for (auto& e : enemies)
    {
        if (e) e->SetPlayer(m_pPlayer);
    }

    for (auto& ui : UIManager::GetUIManager().GetUIList())
    {
        if (ui)ui->SetPlayer(m_pPlayer);
    }
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

// €‚ñ‚Å‚¢‚é“G‚ğíœ
void EnemyManager::RemoveDeadEnemies()
{
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::shared_ptr<EnemyBase>& enemy) {
                return enemy->GetIsDead();  // true‚È‚çíœ
            }),
        enemies.end());
}

// Å’Z‹——£‚Ì“G‚ÌÀ•W‚ğæ“¾
VECTOR EnemyManager::GetNearestEnemyPos(const VECTOR& playerPos)const
{
    VECTOR nearestPos = VGet(0.0f, 0.0f, 0.0f);
    float nearestDist = FLT_MAX;    // ˆê”Ô¬‚³‚¢‹——£‚ğ•Û‘¶

    for (const auto& enemy : enemies)
    {
        // –³Œø or €–S‚µ‚½“G‚ÍƒXƒLƒbƒv
        if (!enemy || enemy->GetIsDead()) continue;

        // ƒvƒŒƒCƒ„[‚Æ‚Ì‹——£‚ğŒvZ
        float dist = VSize(VSub(enemy->GetPosition(), playerPos));

        // ‚æ‚è‹ß‚¢“G‚ğ”­Œ©
        if (dist < nearestDist)
        {
            nearestDist = dist;
            nearestPos = enemy->GetPosition();
        }
    }

    return nearestPos;
}

// Å’Z‹——£‚Ì“G‚ğæ“¾
std::shared_ptr<EnemyBase> EnemyManager::GetNearestEnemy(const VECTOR& playerPos)
{
    std::shared_ptr<EnemyBase> nearestEnemy = nullptr;  // ‰Šú‚Í nullptr
    float nearestDist = FLT_MAX;                        // Å¬‹——£‚ğ‰Šú‰»

    for (const auto& enemy : enemies)
    {
        if (!enemy || enemy->GetIsDead()) continue;    // –³Œø‚È“G‚â€‚ñ‚Å‚é“G‚ÍƒXƒLƒbƒv

        float dist = VSize(VSub(enemy->GetPosition(), playerPos));

        if (dist < nearestDist)
        {
            nearestDist = dist;
            nearestEnemy = enemy;  // ˆê”Ô‹ß‚¢“G‚ğ•Û‘¶
        }
    }

    return nearestEnemy;  // nullptr ‚©AÅ‚à‹ß‚¢“G‚Ì shared_ptr
}
