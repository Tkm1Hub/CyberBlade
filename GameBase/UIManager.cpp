#include "stdafx.h"
#include "UIManager.h"
#include "UIBase.h"

void UIManager::AddUI(std::shared_ptr<UIBase> ui)
{
	m_uiList.push_back(ui);
}

void UIManager::Update()
{
    for (auto& ui : m_uiList)
    {
        if (ui->GetIsActive()) ui->Update();
    }
}

void UIManager::Draw()
{
    for (auto& ui : m_uiList)
    {
        if (ui->GetIsActive()) ui->Draw();
    }
}