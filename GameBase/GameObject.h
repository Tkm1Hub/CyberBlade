#pragma once
#include "DxLib.h"
#include <iostream>
class IGameObject
{
public:
	IGameObject(const std::string& name = ""):name(name){}
	virtual ~IGameObject() {}
	virtual void Init()		{/*�f�t�H���g�ł͉����������Ȃ�*/}
	virtual void Load()		{/*�f�t�H���g�ł͉����������Ȃ�*/}
	virtual void Update()	{/*�f�t�H���g�ł͉����������Ȃ�*/}
	virtual void Draw()		{/*�f�t�H���g�ł͉����������Ȃ�*/}

	VECTOR GetPosition() const { return pos; }
	VECTOR GetNextPosition() const { return nextPos; }
	bool GetIsJumping() { return isJumping; }

	void SetPosition(const VECTOR& newPos) { pos = newPos; }
	void SetNextPosition(const VECTOR& newNextPos) { nextPos = newNextPos; }
	std::string GetName() const { return name; }
	int GetModelHandle() const { return modelHandle; }
	bool GetIsStageCollisionEnabled() const { return isStageCollisionEnabled; }
	bool GetIsCollisionEnabled() const { return isCollisionEnabled; }
	bool GetIsShadowEnebled() const { return isShadowEnabled; }

	virtual const float GetJumpPower() const { return 0; }
	// �����蔻��
	virtual const float GetHitRadius() const { return 0; }
	virtual const float GetHitHeight() const { return 0; }

	virtual void OnFall() {/*�f�t�H���g�ł͉����������Ȃ�*/ }
	virtual void OnHitFloor() {/*�f�t�H���g�ł͉����������Ȃ�*/ }
	virtual void OnHitRoof() {/*�f�t�H���g�ł͉����������Ȃ�*/ }

	virtual const VECTOR GetCapsuleAPos() { return VGet(0.0f, 0.0f, 0.0f); }
	virtual const VECTOR GetCapsuleBPos(){ return VGet(0.0f, 0.0f, 0.0f); }

protected:
	std::string name = "null";
	VECTOR pos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR nextPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR rotate = VGet(0.0f, 0.0f, 0.0f);
	VECTOR modelScale = VGet(0.0f, 0.0f, 0.0f);
	int modelHandle = -1;
	bool isStageCollisionEnabled = false;					// �X�e�[�W�Ƃ̓����蔻���L���ɂ��邩
	bool isCollisionEnabled = false;						// �����蔻���L���ɂ��邩
	bool isShadowEnabled = false;							// �e�̕`���L���ɂ��邩
	bool isJumping = false;									// �W�����v����
};