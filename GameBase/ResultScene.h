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

    int imgHandle = -1;

    int titleHandle = -1;
    int titleBackHandle = -1;

    int player_ModelHandle = -1;

    int ALPHA_SPEED = 2;

    VECTOR playerModelPos = { -770.0f,-9020.0f,2000.0f };
    VECTOR playerModelScale = { 50.0f,50.0f,50.0f };

    std::shared_ptr<Animation> animation = nullptr;
};