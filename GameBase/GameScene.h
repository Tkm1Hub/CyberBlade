#pragma once
#include "Scene.h"

class ObjectManager;
class CollisionManager;
class ShadowManager;
class Debug;
class GameScene :public Scene
{
public:
    /// @brief SceneManager �ւ̎Q�Ƃ��󂯎��܂��B
// @param manager SceneManager �ւ̎Q��
    GameScene(SceneManager& manager);
    ~GameScene();

    /// @brief �^�C�g�������������܂��B
    void Init() override;

    /// @brief �^�C�g�����X�V���܂��B
    void Update() override;

    /// @brief �^�C�g����`�悵�܂��B
    void Draw() const override;

private:
    std::shared_ptr<ObjectManager> objectMgr = nullptr;
    std::shared_ptr<CollisionManager> collisionMgr = nullptr;
    std::shared_ptr<ShadowManager> shadowMgr = nullptr;
    std::shared_ptr<Debug> debug = nullptr;
};