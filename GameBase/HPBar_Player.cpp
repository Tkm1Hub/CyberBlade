#include "stdafx.h"
#include "HPBar_Player.h"
#include "Player.h"

void HPBar_Player::Init()
{
	m_isActive = true;
	m_pos = VGet(OFFSET_X, OFFSET_Y, 0);

	if (auto player = m_pPlayer.lock())
	{
		currentHp = player->GetHitPoint();
		prevHp = currentHp;
	}
}

void HPBar_Player::Update()
{
	if (auto player = m_pPlayer.lock())
	{
		currentHp = player->GetHitPoint();
		float hpRate = static_cast<float>(currentHp) / player->GetMaxHp();

		// HPが減った？
		if (hpRate < prevHpRate)
		{
			// 減った割合 = 前の割合 - 今の割合
			damageBarRate = prevHpRate - hpRate;

			// 表示フラグON
			isDrawDamage = true;
			frameCount = 0;
		}

		// ダメージバーの表示時間カウント
		if (isDrawDamage)
		{
			frameCount++;
			if (frameCount > 60)
			{
				isDrawDamage = false;
			}
		}

		prevHpRate = hpRate;
	}
}

void HPBar_Player::Draw()
{

	if (auto player = m_pPlayer.lock())
	{
		int hp = player->GetHitPoint();
		int maxHp = player->GetMaxHp();
		if (maxHp <= 0) maxHp = 1;

		float hpRate = static_cast<float>(hp) / maxHp;
		hpRate = std::clamp(hpRate, 0.0f, 1.0f);

		int hpWidth = static_cast<int>(WIDTH * hpRate);

		// バー背景
		DrawBox(m_pos.x, m_pos.y,
			m_pos.x + WIDTH, m_pos.y + HEIGHT,
			GetColor(56, 58, 53), TRUE);

		// ダメージ部分バー
		if (isDrawDamage)
		{
			int damageBarWidth = static_cast<int>(WIDTH * damageBarRate);

			// 減った部分の開始位置 = 現在HPバーの右端
			int start = m_pos.x + hpWidth;

			DrawBox(start, m_pos.y,
				start + damageBarWidth, m_pos.y + HEIGHT,
				GetColor(181, 90, 68), TRUE);  // 赤っぽい色
		}

		// 現在のHPバー
		DrawBox(m_pos.x, m_pos.y,
			m_pos.x + hpWidth, m_pos.y + HEIGHT,
			GetColor(204, 200, 175), TRUE);
	}
}