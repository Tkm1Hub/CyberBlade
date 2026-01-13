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

    bool isChangeScene = false;
    int fade = 0;

    int fontHandle = -1;

    int titleHandle = -1;
    int titleBackHandle = -1;

    int player_ModelHandle = -1;
    int sword_ModelHandle = -1;

    int movie_Handle = -1;
    int movie_x = 650;

    int title_y = 175;
    int title_alpha = 0;

    int stringPos_x = 1155;
    int stringPos_y = 865;
    int string_alpha = 40;

    int ALPHA_SPEED = 2;

    static constexpr int TITLE_X_OFFSET = 643;
    static constexpr int TITLE_Y_MAX = 1112;
    static constexpr int TITLE_HEIGHT = 973;
    static constexpr int TITLE_WIDTH = 1335;
    static constexpr int TITLE_DOWN_SPEED = 5;

    static constexpr int TITLE_X1 = 643;
    static constexpr int TITLE_Y1 = 175;
    static constexpr int TITLE_X2 = 1998;
    static constexpr int TITLE_Y2 = 1112;

    VECTOR playerModelPos = { -770.0f,-9020.0f,2000.0f };
    VECTOR playerModelScale = { 50.0f,50.0f,50.0f };

    VECTOR swordModelPos = { -450.0f,-3320.0f,800.0f };
    VECTOR swordModelScale = { 50.0f,50.0f,50.0f };
    VECTOR swordModelRot = { -0.07f,0.0f,0.0f };

    VECTOR lightDir = { -0.87f,-1.0f,3.11f };
    VECTOR lightPos = { 10000.0f,10000.0f,1500.0f };

    std::shared_ptr<Animation> animation = nullptr;
};