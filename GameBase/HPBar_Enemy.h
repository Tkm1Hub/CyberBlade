#pragma once
#include "UIBase.h"

class EnemyBase;
class HPBar_Enemy :public UIBase
{
public:
    void Init() override;
    void Update() override;
    void Draw() override;

    void SetEnemy(std::weak_ptr<EnemyBase> enemy) { m_pEnemy = enemy; }

private:
    std::weak_ptr<EnemyBase> m_pEnemy;  // “G‚ÌQÆ

    static constexpr int WIDTH = 130;   // ‰¡•
    static constexpr int HEIGHT = 8;   // c•

    static constexpr float ACTIVE_RADIUS = 80.0f;   // •\¦‚·‚é”ÍˆÍ
};
