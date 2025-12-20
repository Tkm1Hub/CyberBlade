#pragma once
#include "Scene.h"

class Animation;
class TitleScene :public Scene
{
public:
    /// @brief SceneManager への参照を受け取ります。
// @param manager SceneManager への参照
    TitleScene(SceneManager& manager);
    ~TitleScene();

    /// @brief タイトルを初期化します。
    void Init() override;

    /// @brief タイトルを更新します。
    void Update() override;

    /// @brief タイトルを描画します。
    void Draw() const override;

private:

    int titleHandle = -1;
    int titleBackHandle = -1;

    int player_ModelHandle = -1;
    int sword_ModelHandle = -1;

    static constexpr int TITLE_X1 = 643;
    static constexpr int TITLE_Y1 = 175;
    static constexpr int TITLE_X2 = 1998;
    static constexpr int TITLE_Y2 = 1112;

    VECTOR playerModelPos = { 0.0f,0.0f,10.0f };
    VECTOR playerModelScale = { 5.0f,5.0f,5.0f };
};