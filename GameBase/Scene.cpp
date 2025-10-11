#include "stdafx.h"
#include "Scene.h"
#include "SceneManager.h"

Scene::Scene(SceneManager& manager)
    : m_manager{ manager } {
}

void Scene::Init()
{
    // ������
}

void Scene::Update()
{
    // ������
}

void Scene::Draw() const
{
    // ������
}

void Scene::ChangeScene(const std::string_view name)
{
    m_manager.ChangeScene(name);
}
