#include "stdafx.h"
#include "HPBar_Enemy.h"
#include "EnemyBase.h"
#include "Player.h"

void HPBar_Enemy::Init()
{
	m_isActive = true;
}

void HPBar_Enemy::Update()
{

	if (auto enemy = m_pEnemy.lock())
	{
		bool isActive = true;

		// 死亡してたら非表示にして終了
		if (enemy->GetIsDead())
		{
			isActive = false;
		}
		else
		{
			//if (enemy->GetName() == "EnemyBoss")
			//{
			//	isActive = false;
			//}
			// 距離チェック
			if (auto p = m_pPlayer.lock())
			{
				VECTOR diff = VSub(p->GetPosition(), enemy->GetPosition());
				float dist = VSize(diff);
				if (dist > ACTIVE_RADIUS)
				{
					isActive = false;
				}
			}

			// スクリーン座標に変換
			m_pos = ConvWorldPosToScreenPos(enemy->GetHPBarPos());

			// カメラに写っていない場合 → 非表示
			if (CheckCameraViewClip(enemy->GetHPBarPos()))
			{
				// 見えない
				isActive = false;
			}
		}

		if (enemy->GetName() == "EnemyBoss")
		{
			isActive = false;
		}

		m_isActive = isActive;
	}
	else
	{
		m_isActive = false;
	}
}

void HPBar_Enemy::Draw()
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
		DrawBox(m_pos.x - WIDTH / 2, m_pos.y - HEIGHT / 2, m_pos.x + WIDTH / 2, m_pos.y + HEIGHT / 2, GetColor(56, 58, 53), TRUE);
		// HPを描画
		DrawBox(m_pos.x - WIDTH / 2, m_pos.y - HEIGHT / 2, (m_pos.x - WIDTH / 2) + currentWidth, m_pos.y + HEIGHT / 2, GetColor(204, 200, 175), TRUE);
	}
	
}