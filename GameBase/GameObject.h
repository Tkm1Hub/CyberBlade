#pragma once
#include "DxLib.h"
#include <iostream>
class IGameObject
{
public:
	IGameObject(const std::string& name = ""):name(name){}
	virtual ~IGameObject() {}
	virtual void Init()		{/*デフォルトでは何も実装しない*/}
	virtual void Load()		{/*デフォルトでは何も実装しない*/}
	virtual void Update()	{/*デフォルトでは何も実装しない*/}
	virtual void Draw()		{/*デフォルトでは何も実装しない*/}

	VECTOR GetPosition() const { return pos; }
	VECTOR GetNextPosition() const { return nextPos; }
	float GetAngleH() const { return angleH; }
	void SetAngleH(float dir) { angleH = dir; }
	const float GetAngleV() const { return angleV; }
	void SetAngleV(float dir) { angleV = dir; }
	const bool GetIsJumping() const { return isJumping; }

	void SetPosition(const VECTOR& newPos) { pos = newPos; }
	void SetNextPosition(const VECTOR& newNextPos) { nextPos = newNextPos; }
	std::string GetName() const { return name; }
	int GetModelHandle() const { return modelHandle; }
	bool GetIsStageCollisionEnabled() const { return isStageCollisionEnabled; }
	bool GetIsCollisionEnabled() const { return isCollisionEnabled; }
	bool GetIsShadowEnebled() const { return isShadowEnabled; }

	virtual const float GetJumpPower() const { return 0; }
	// 当たり判定
	virtual const float GetHitRadius() const { return 0; }
	virtual const float GetHitHeight() const { return 0; }

	virtual void OnFall() {/*デフォルトでは何も実装しない*/ }
	virtual void OnHitFloor() {/*デフォルトでは何も実装しない*/ }
	virtual void OnHitRoof() {/*デフォルトでは何も実装しない*/ }

	virtual const VECTOR GetTopPos() { return VGet(0.0f, 0.0f, 0.0f); }
	virtual const VECTOR GetBottomPos(){ return VGet(0.0f, 0.0f, 0.0f); }

	const VECTOR GetLockOnPos() { return lockOnPos; }

protected:
	std::string name = "null";
	VECTOR pos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR nextPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR lockOnPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR rotate = VGet(0.0f, 0.0f, 0.0f);
	VECTOR modelScale = VGet(0.0f, 0.0f, 0.0f);
	int modelHandle = -1;
	bool isStageCollisionEnabled = false;					// ステージとの当たり判定を有効にするか
	bool isCollisionEnabled = false;						// 当たり判定を有効にするか
	bool isShadowEnabled = false;							// 影の描画を有効にするか
	float angleH = 0.0f;									// 水平角度
	float angleV = 0.0f;									// 垂直角度
	bool isJumping = false;									// ジャンプ中か

};