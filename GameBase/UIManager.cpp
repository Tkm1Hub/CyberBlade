#include "stdafx.h"
#include "UIManager.h"
#include "UIBase.h"
#include "Marker.h"

void UIManager::Init()
{
    marker = std::make_shared<Marker>();

    if (auto p = m_pPlayer.lock())
    {
        marker->SetPlayer(p);
        AddUI(marker);
    }
}

void UIManager::AddUI(std::shared_ptr<UIBase> ui)
{
	m_uiList.push_back(ui);
}

void UIManager::Update()
{
    for (auto& ui : m_uiList)
    {
        ui->Update();
    }
}

void UIManager::Draw()
{
    for (auto& ui : m_uiList)
    {
        if (ui->GetIsActive()) ui->Draw();
    }
}