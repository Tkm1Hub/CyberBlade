#pragma once
#include "Scene.h"

/// @brief �V�[���}�l�[�W���[
/// @remark ���̃N���X�ŊǗ�����V�[���� Scene ���p������K�v������܂��B
class SceneManager
{
public:

    SceneManager();

    /// @brief �����o�ϐ��̌�n�������܂��B
    ~SceneManager();

    /// @brief �A�N�e�B�u�ȃV�[�����X�V���܂��B
    /// @remark �A�N�e�B�u�ȃV�[����������Ή������܂���B
    void Update() const;

    /// @brief �A�N�e�B�u�ȃV�[����`�悵�܂��B
    /// @remark �A�N�e�B�u�ȃV�[����������Ή������܂���B
    void Draw() const;

    /// @brief �Ǘ�����V�[����ǉ����܂��B
    /// @tparam SceneType �Ǘ�����V�[���̌^
    /// @param name �V�[����
    /// @note �e���v���[�g�֐��̓C�����C����`����K�v������܂��B
    /// @warning SceneType �͂ǂ�Ȍ^�ł����e���Ă��܂��̂ŁA�R���Z�v�g�� SFINAE �Ő����t����K�v������܂��B
    template <class SceneType>
    void Add(const std::string_view name)
    {
        // [HACK] �d���񋖗e�ɂ���K�v������܂��B
        m_scenes[name] = new SceneType{ *this };

        // �ŏ��ɒǉ����ꂽ�V�[�����f�t�H���g�̃V�[���ł��B
        if (m_nowScene == nullptr)
        {
            m_nowScene = m_scenes[name];
            m_nowScene->Init();
        }
    }

    /// @brief �A�N�e�B�u�ȃV�[����؂�ւ��܂��B
    /// @param name �؂�ւ���̃V�[����
    void ChangeScene(std::string_view name);

private:

    /// @brief �V�[���R���e�i
    std::unordered_map<std::string_view, Scene*> m_scenes;

    /// @brief �A�N�e�B�u�ȃV�[��
    Scene* m_nowScene;
};
