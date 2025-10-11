#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager()
    : m_nowScene{ nullptr } {
}

SceneManager::~SceneManager()
{
    for (const auto& pair : m_scenes)
    {
        delete pair.second;
    }
}

void SceneManager::Update() const
{
    if (m_nowScene != nullptr)
    {
        m_nowScene->Update();
    }
}

void SceneManager::Draw() const
{
    if (m_nowScene != nullptr)
    {
        m_nowScene->Draw();
    }
}

void SceneManager::ChangeScene(const std::string_view name)
{
#ifdef _DEBUG

    try
    {
        m_nowScene = m_scenes.at(name);
        m_nowScene->Init();
    }
    catch (...)
    {
        assert(!"���݂��Ȃ��L�[���w�肳��܂����B");
    }

#else

    m_nowScene = m_scenes[name];
    m_nowScene->Initialize();

#endif
}
