#pragma once
#include "UIBase.h"

class Player;
class HPBar_Player :public UIBase
{
public:
    void Init() override;
    void Update() override;
    void Draw() override;

private:
    static constexpr int WIDTH = 400;   // 横幅
    static constexpr int HEIGHT = 30;   // 縦幅

    static constexpr float OFFSET_X = 30.0f;            // X座標
    static constexpr float OFFSET_Y = 1000.0f;            // Y座標

    int frameCount = 0;

    float prevHp = 0.0f;
    float currentHp = 0.0f;
    float prevHpRate = 1.0f;       // ダメージ前のHP割合
    float damageBarRate = 0.0f;    // 減った量（割合）
    bool isDrawDamage = false;          // ダメージ量を描画
};
