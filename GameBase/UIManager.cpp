#include "stdafx.h"
#include "UIManager.h"
#include "UIBase.h"
#include "Marker.h"
#include "HPBar_Player.h"
#include "HPBar_Boss.h"

void UIManager::Init()
{
    marker = std::make_shared<Marker>();
    hpBar_Player = std::make_shared<HPBar_Player>();
    hpBar_Boss = std::make_shared<HPBar_Boss>();

    if (auto p = m_pPlayer.lock())
    {
        marker->SetPlayer(p);
        AddUI(marker);

        hpBar_Player->SetPlayer(p);
        AddUI(hpBar_Player);
        hpBar_Player->Init();

    }

    if (auto e = m_pEnemyBig.lock())
    {
        hpBar_Boss->SetEnemy(e);
        AddUI(hpBar_Boss);
        hpBar_Boss->Init();
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