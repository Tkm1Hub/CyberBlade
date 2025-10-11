#pragma once
#include "Character.h"
#include "StateMachine.h"
#include "Animation.h"
#include "PlayerStateBase.h"

// パラメータ
struct PlayerParams
{
	float JumpPower = 2.5f;		// ジャンプ力
	float Gravity = 0.08f;		// 重力
	float WalkSpeed = 0.5f;		// 歩き移動速度
	float RunSpeed = 1.5f;		// 走り移動速度
	float Attack1MoveSpeed = 0.7f;	// 攻撃1段階目での前方移動速度
	float Attack2MoveSpeed = 0.9f;	// 攻撃2段階目での前方移動速度
	float Attack3MoveSpeed = 0.5f;	// 攻撃3段階目での前方移動速度
	float AttackDashMoveSpeed = 1.5f;	// 走り攻撃での前方移動速度
	float Accel = 0.01f;		// 移動加速度
	float decel = 0.03f;		// 移動減速度
	float AngleSpeed = 0.2f;	// 移動時のモデル回転速度
	float HitRadius = 3.0f;		// 当たり判定半径
	float HitHeight = 16.5f;	// 当たり判定高さ
	VECTOR InitPos = { 0.0f,0.0f,0.0f };	// 初期座標
};

// アニメーション番号
enum class PlayerAnimState :int
{
	None = -1,      // なし
	TPose = 0,      // 不明
	Idle = 1,       // アイドル
	Walk = 2,       // 歩き
	Run = 3,        // 走り
	RunPose = 4,    // ダッシュポーズ
	RunStop = 6,    // ストップ
	Jump = 7,       // ジャンプ
	Fall = 8,       // 落下中
	Attack1 = 9,		// 通常攻撃（1段階）
	Attack2 = 10,	// 通常攻撃（2段階）
	Attack3 = 11,	// 通常攻撃（3段階）
	AttackDash = 12,	// 走り攻撃
};

class PayerStateBase;
class Player :public Character
{
public:
	Player(const std::string& name) : Character(name){}

	void Init() override;
	void Load() override;
	void Update() override;
	void Draw() override;

	void ChangeState(std::shared_ptr<PlayerStateBase> a_spState);

	// フラグセッター
	void SetRunFlag(bool flag) { isRunning = flag; }
	void SetMoveFrag(bool flag) { isMove = flag; }
	void SetAttackFrag(bool flag) { isAttack = flag; }

	const bool GetIsAttack()const { return isAttack; }

	const float GetHitRadius() const override { return params.HitRadius; }
	const float GetHitHeight() const override { return params.HitHeight; }

	const MATRIX GetHandMatrix()const { return handMatrix; }

	void OnHitRoof() override;       // 天井に当たった時
	void OnHitFloor() override;      // 床に当たった時
	void OnFall() override;          // 落下が確定したとき

	VECTOR GetMoveInput();		// スティックによる移動ベクトルの取得
	const VECTOR GetTargetMoveDirection() const { return targetMoveDirection; }	// モデルが向くべき方向を取得

	Animation animation;		// アニメーション
	const PlayerParams GetParams() const { return params; }

private:
	StateMachine stateMachine;	// ステートマシン
	PlayerParams params;		// パラメータ

	MATRIX handMatrix;

	int handBoneIndex = -1;		// 手のボーンの番号

	bool isRunning = false;		// 走っているか
	bool isAttack = false;		// 攻撃中か

	void Move();	// モデルの移動
	void CulcMoveSpeed();	// 移動速度の計算

	void UpdateAngle();			// モデルの角度更新

};