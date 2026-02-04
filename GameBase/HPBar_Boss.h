#pragma once
#include "UIBase.h"

class EnemyBig;
class HPBar_Boss :public UIBase
{
public:
    void Init() override;
    void Update() override;
    void Draw() override;

    void SetEnemy(std::weak_ptr<EnemyBig> enemy) { m_pEnemy = enemy; }

private:
    std::weak_ptr<EnemyBig> m_pEnemy;  // “G‚ÌQÆ

    static constexpr int WIDTH = 878;   // ‰¡•
    static constexpr int HEIGHT = 28;   // c•

};
