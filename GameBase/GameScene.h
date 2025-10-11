#pragma once
#include "Scene.h"

class ObjectManager;
class CollisionManager;
class ShadowManager;
class Debug;
class GameScene :public Scene
{
public:
    /// @brief SceneManager への参照を受け取ります。
// @param manager SceneManager への参照
    GameScene(SceneManager& manager);
    ~GameScene();

    /// @brief タイトルを初期化します。
    void Init() override;

    /// @brief タイトルを更新します。
    void Update() override;

    /// @brief タイトルを描画します。
    void Draw() const override;

private:
    std::shared_ptr<ObjectManager> objectMgr = nullptr;
    std::shared_ptr<CollisionManager> collisionMgr = nullptr;
    std::shared_ptr<ShadowManager> shadowMgr = nullptr;
    std::shared_ptr<Debug> debug = nullptr;
};