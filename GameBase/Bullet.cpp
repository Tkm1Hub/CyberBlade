#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	Init();
}

Bullet::~Bullet() {}

// 初期化
void Bullet::Init()
{
	name = "Bullet";
	pos = VGet(0.0f, 0.0f, 0.0f);
	modelHandle = -1;

	active = false;
	moveVec = VGet(0.0f, 0.0f, 0.0f);
}

void Bullet::Load() {}

// 更新処理
void Bullet::Update()
{
	// 無効なら早期リターン
	if (!active) return;
	Move();

	lifeCount--;

	if (lifeCount <= 0)
	{
		Reset();
	}
}

// 描画処理
void Bullet::Draw()
{
	// 無効なら早期リターン
	if (!active) return;
	DrawSphere3D(pos, RADIUS, DIVNUM, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
}

// 弾の移動
void Bullet::Move()
{
	moveVec = VNorm(moveVec);
	moveVec = VScale(moveVec, speed);
	pos = VAdd(pos, moveVec);
}

// プレイヤーに当たった際の処理
void Bullet::HitPlayer()
{
	// プレイヤーに当たったら非表示
	active = false;
	pos = VGet(0.0f, 0.0f, 0.0f);
}

// 有効化
void Bullet::Activate()
{
	active = true;
	lifeCount = LIFETIME;
}

// 無効化
void Bullet::Reset()
{
	active = false;
	pos = VGet(0.0f, 0.0f, 0.0f);
}