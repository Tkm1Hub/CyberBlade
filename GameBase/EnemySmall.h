#pragma once
#include "EnemyBase.h"
#include "StateMachine.h"

// パラメータ
struct EnemySmall_Params
{
	float Gravity = 0.08f;		// 重力
	float DamageSpeed = 1.5f;	// ダメージ中ノックバックの速度
	float HitRadius = 4.0f;		// 当たり判定半径
	float HitHeight = 14.0f;	// 当たり判定高さ
	VECTOR InitPos = { 0.0f,0.0f,30.0f };	// 初期座標
};

class EnemySmallStateBase;
class EnemySmall :public EnemyBase
{
public:
	EnemySmall(const std::string& name):EnemyBase(name){}

	void Init() override;
	void Load() override;
	void Update() override;

	void SetDamageFlag(bool flag) { isDamage = flag; }
	const bool GetDamageFlag() const { return isDamage; }

	void ChangeState(std::shared_ptr<EnemySmallStateBase> a_spState);

	VECTOR GetKnockBackDir()const { return knockBackDir; }
	void SetKnockBackDir(const VECTOR& direction) { knockBackDir = direction; }

	const float GetHitRadius() const override { return params.HitRadius; }
	const float GetHitHeight() const override { return params.HitHeight; }

	void OnHitRoof() override;       // 天井に当たった時
	void OnHitFloor() override;      // 床に当たった時
	void OnFall() override;          // 落下が確定したとき

	const EnemySmall_Params GetParams() const { return params; }
private:
	EnemySmall_Params params;	// パラメータ
	StateMachine stateMachine;	// ステートマシン

	VECTOR knockBackDir = { 0.0f,0.0f,0.0f };

	bool isDamage = false;

};