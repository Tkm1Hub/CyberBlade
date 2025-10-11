#pragma once

class SceneManager;

/// @brief �V�[���̊��N���X
/// @remark SceneManager �ŊǗ�����V�[���͂��̃N���X���p������K�v������܂��B
class Scene
{
public:

    /// @brief SceneManager �ւ̎Q�Ƃ��󂯎��܂��B
    /// @param manager SceneManager �ւ̎Q��
    Scene(SceneManager& manager);

    /// @brief �V�[�������������܂��B
    /// @remark �f�t�H���g�ł͉������܂���B
    virtual void Init();

    /// @brief �V�[�����X�V���܂��B
    /// @remark �f�t�H���g�ł͉������܂���B
    virtual void Update();

    /// @brief �V�[����`�悵�܂��B
    /// @remark �f�t�H���g�ł͉������܂���B
    virtual void Draw() const;

protected:

    /// @brief �A�N�e�B�u�ȃV�[����؂�ւ��܂��B
    /// @param name �؂�ւ���̃V�[����
    void ChangeScene(std::string_view name);

private:

    /// @brief SceneManager �ւ̎Q��
    /// @note �|�C���^���g�������S�ł��B
    SceneManager& m_manager;
};
