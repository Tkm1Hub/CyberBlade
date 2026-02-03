#pragma once
#include "GameObject.h"

class Bullet :public IGameObject
{
public:
	Bullet();
	~Bullet();

	void Init() override;
	void Load() override;
	void Update() override;
	void Draw() override;

	const VECTOR& GetPos() const { return pos; }
	float GetRadius() const { return RADIUS; }

	void HitPlayer();
	void Activate();
	void Reset();

	bool IsActive() const { return active; }

	void SetPosition(const VECTOR setPos) { pos = setPos; }
	void SetMoveVec(const VECTOR setMoveVec) { moveVec = setMoveVec; }

private:
	// 定数
	static constexpr float RADIUS = 3.0f;	// 弾の半径
	static constexpr int LIFETIME = 300;	// 弾が消えるまでのフレーム数
	static constexpr int DIVNUM = 32;		// ポリゴンの細かさ

	// 変数
	float speed = 0.65f;							// 弾の速度
	bool active = false;						// 動作中か
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);	// 移動ベクトル
	int lifeCount = 0;							// 弾が発射されてからのフレーム

	void Move();
};