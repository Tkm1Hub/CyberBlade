#pragma once
#include "Scene.h"

class Animation;
class ResultScene :public Scene
{
public:
    /// @brief SceneManager への参照を受け取ります。
// @param manager SceneManager への参照
    ResultScene(SceneManager& manager);
    ~ResultScene();

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

};