#include "stdafx.h"
#include "HPBar_Boss.h"
#include "EnemyBig.h"
#include "Player.h"

void HPBar_Boss::Init()
{
	m_isActive = true;
}

void HPBar_Boss::Update()
{

	if (auto enemy = m_pEnemy.lock())
	{
		bool isActive = true;

		// 死亡してたら非表示にして終了
		if (enemy->GetIsDead())
		{
			isActive = false;
		}
	}
	else
	{
		m_isActive = false;
	}
}

void HPBar_Boss::Draw()
{

	if (auto enemy = m_pEnemy.lock())
	{
		// 敵のHPと最大HPは int を想定
		int hp = enemy->GetHp();
		int maxHp = enemy->GetMaxHp();

		// ゼロ除算を防ぐ
		if (maxHp <= 0) maxHp = 1;

		// 正しく float にキャストしてから割る
		float hpRate = static_cast<float>(hp) / static_cast<float>(maxHp);

		// 安全のため 0.0f ～ 1.0f にクランプ
		hpRate = std::clamp(hpRate, 0.0f, 1.0f);

		// 現在の横幅（丸めて整数に）
		int currentWidth = static_cast<int>(std::round(WIDTH * hpRate));
		// ボックスを描画
		DrawBox(960 - WIDTH / 2, 100 - HEIGHT / 2, 960 + WIDTH / 2, 100 + HEIGHT / 2, GetColor(56, 58, 53), TRUE);
		// HPを描画
		DrawBox(960 - WIDTH / 2, 100 - HEIGHT / 2, (960 - WIDTH / 2) + currentWidth, 100 + HEIGHT / 2, GetColor(204, 200, 175), TRUE);
	}

}