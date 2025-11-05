#pragma once
#include "EnemyBase.h"
#include "StateMachine.h"

// パラメータ
struct EnemySmall_Params
{
	int MaxHp = 120;						// 最大HP

	float Gravity = 0.08f;					// 重力
	float DamageSpeed = 1.5f;				// ダメージ中ノックバックの速度
	float HitRadius = 4.0f;					// 当たり判定半径
	float HitHeight = 14.0f;				// 当たり判定高さ
	float ChaseTriggerDistance = 60.0f;		// 追跡を開始するプレイヤーとの距離
	float AttackTriggerDistance = 30.0f;	// 攻撃を開始するプレイヤーとの距離
	float Accel = 0.03f;					// 移動加速度
	float Decel = 0.1f;						// 移動減速度
	float ChaseSpeed = 0.3f;				// 追跡速度
};

class EnemySmallStateBase;
class EnemySmall :public EnemyBase
{
public:
	EnemySmall(const std::string& name):EnemyBase(name){}

	void Init() override;
	void Load() override;
	void Update() override;

	void ChangeState(std::shared_ptr<EnemySmallStateBase> a_spState);

	const float GetHitRadius() const override { return params.HitRadius; }
	const float GetHitHeight() const override { return params.HitHeight; }

	void OnHitRoof() override;       // 天井に当たった時
	void OnHitFloor() override;      // 床に当たった時
	void OnFall() override;          // 落下が確定したとき

	const EnemySmall_Params GetParams() const { return params; }
private:
	EnemySmall_Params params;	// パラメータ
	StateMachine stateMachine;	// ステートマシン

};