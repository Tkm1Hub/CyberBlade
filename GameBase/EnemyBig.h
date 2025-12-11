#pragma once
#include "EnemyBase.h"
#include "StateMachine.h"

// パラメータ
struct EnemyBig_Params
{
	int MaxHp = 1000;						// 最大HP

	float Gravity = 0.2f;					// 重力
	float AttackMoveSpeed = 1.5f;			// 攻撃中前進速度
	float DodgeJumpPower = 2.0f;			// 回避中のジャンプ力
	float DodgeMoveSpeed = 4.0f;			// 回避中の移動速度
	float DamageSpeed = 1.5f;				// ダメージ中ノックバックの速度
	float AttackJumpPower = 5.3f;			// ジャンプ攻撃の高度
	float HitRadius = 25.0f;				// 当たり判定半径
	float HitHeight = 40.0f;				// 当たり判定高さ
	float LeftHandHitRadius = 15.0f;		// 左手の当たり判定
	float RightHandHitRadius = 30.0f;		// 右手の当たり判定
	float HipHitRadius = 50.0f;				// 腰の当たり判定
	float HPBarHeight = 20.0f;				// HPバーを表示する高さ
	float WarningDistance = 150.0f;			// 警戒を開始するプレイヤーとの距離
	float AttackTriggerRadius = 80.0f;		// Attackを開始するプレイヤーとの距離
	float Accel = 0.03f;					// 移動加速度
	float Decel = 0.1f;						// 移動減速度
	float ChaseSpeed = 2.0f;				// 追跡速度

	VECTOR scale = { 0.35,0.35,0.35 };
};

// アニメーション番号
enum class EnemyBigAnimState :int
{
	None = -1,			// なし
	Idle = 0,			// 立ち止まり
	Chase = 1,			// 追跡
	Attack = 2,			// 攻撃
	AttackJump = 4,		// ジャンプ攻撃
	Slash1 = 10,		// 薙ぎ払い１
	Slash2 = 11,		// 薙ぎ払い２
	Warning = 6,		// 警戒
	Dodge = 8,			// 回避
	CastPose = 12,		// 弾幕中
};


class EnemyBigStateBase;
class EnemyBig :public EnemyBase
{
public:
	EnemyBig(const std::string& name) :EnemyBase(name) {}

	void Init() override;
	void Load() override;
	void Update() override;

	void ChangeState(std::shared_ptr<EnemyBigStateBase> a_spState);

	const float GetHitRadius() const override { return params.HitRadius; }
	const float GetHitHeight() const override { return params.HitHeight; }

	void OnHitRoof() override;       // 天井に当たった時
	void OnHitFloor() override;      // 床に当たった時
	void OnFall() override;          // 落下が確定したとき

	const float GetWarningRadius()const { return params.WarningDistance; }
	const float GetAttack1TriggerRadius() const { return params.AttackTriggerRadius; }

	const EnemyBig_Params GetParams() const { return params; }

private:
	EnemyBig_Params params;	// パラメータ
	StateMachine stateMachine;	// ステートマシン


	int damageFrameCount = 0;
	void UpdateDamageFlag();
};