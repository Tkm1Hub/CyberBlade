#include "stdafx.h"
#include "BulletCreator.h"
#include "Bullet.h"

void BulletCreator::Init()
{
	// 仮に200発用意
	for (int i = 0; i < BULLET_NUM + 1; i++)
	{
		bullets.push_back(std::make_shared<Bullet>());
	}
}

void BulletCreator::Update()
{
	// 有効な弾の更新
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Update();
		}
	}
}

// 弾の発射（生成する座標 , 発射する方向）
void BulletCreator::Create(const VECTOR& pos, const VECTOR& moveVec)
{
	for (auto& bullet : bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Activate();
			bullet->SetPosition(pos);
			bullet->SetMoveVec(moveVec);
			return;	// 1発のみ生成してループ解除
		}
	}
}

void BulletCreator::Draw()
{
	for (auto& bullet : bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Draw();
		}
	}
}