#pragma once
#include "Scene.h"

class TitleScene :public Scene
{
public:
    /// @brief SceneManager �ւ̎Q�Ƃ��󂯎��܂��B
// @param manager SceneManager �ւ̎Q��
    TitleScene(SceneManager& manager);
    ~TitleScene();

    /// @brief �^�C�g�������������܂��B
    void Init() override;

    /// @brief �^�C�g�����X�V���܂��B
    void Update() override;

    /// @brief �^�C�g����`�悵�܂��B
    void Draw() const override;

private:

};