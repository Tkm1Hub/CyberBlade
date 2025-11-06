#pragma once
#include "Character.h"
#include "StateMachine.h"
#include "Animation.h"
#include "PlayerStateBase.h"

// パラメータ
struct PlayerParams
{
	// フレーム関連

	// 攻撃１
	static constexpr int ATTACK_1_NEXT_ATTACK_WAIT_FRAMES = 18;		// 次の攻撃が出せるまで
	static constexpr int ATTACK_1_RECOVERY_FRAMES = 48;				// 移動できるようになるまで
	static constexpr int ATTACK_2_RECOVERY_FRAMES = 48;			// 攻撃２の硬直時間
	static constexpr int ATTACK_3_RECOVERY_FRAMES = 48;			// 攻撃３の硬直時間
	static constexpr int ATTACK_DASH_RECOVERY_FRAMES = 48;		// ダッシュ攻撃の硬直時間
	static constexpr int ATTACK_JUMP_1_RECOVERY_FRAMES = 48;	// ジャンプ攻撃１の硬直時間

	static constexpr int JUMP_MAX_COUNT = 2;					// 連続ジャンプの最大数
	static constexpr int JUMP_START_WAIT_FRAMES = 8;			// ジャンプするまでの待機時間
	static constexpr int JUMP_1_TO_2_WAIT_FRAMES = 24;			// 二段ジャンプの待機時間

	static constexpr int ATTACK_DODGE_INPUT_WINDOW_FRAMES = 5;	// 回避攻撃の入力受付時間

	static constexpr int DODGE_BACK_BOOST_WAIT_FRAMES = 14;	// 後方回避のブーストまでの待機時間
	static constexpr int DODGE_RECOVERY_FRAMES = 24;		// 回避の硬直時間

	// パラメータ
	float Jump1Power = 3.0f;			// ジャンプ力（1段目）
	float Jump2Power = 3.5f;			// ジャンプ力（2段目）
	float Gravity = 0.12f;				// 重力
	float WalkSpeed = 0.4f;				// 歩き最大移動速度
	float SlowRunSpeed = 0.9f;			// 小走り最大移動速度
	float RunSpeed = 1.5f;				// 走り最大移動速度
	float FallMaxMoveSpeed = 1.5f;		// 落下中の最大移動速度
	float DodgeStartSpeed = 1.8f;		// 回避開始速度
	float DodgeSpeed = 2.0f;			// 回避最大速度
	float DodgeSpeedDecel = 0.1f;		// 回避スピードの減速度
	float Attack1MoveSpeed = 0.7f;		// 攻撃1段階目での前方移動速度
	float Attack2MoveSpeed = 0.9f;		// 攻撃2段階目での前方移動速度
	float Attack3MoveSpeed = 0.5f;		// 攻撃3段階目での前方移動速度
	float AttackJump1MoveSpeed = 2.0f;	// 空中攻撃1段階目での前方移動速度
	float AttackDashMoveSpeed = 1.5f;	// 走り攻撃での前方移動速度
	float AttackFallSpeed = 0.06f;		// 空中攻撃時の落下加速度
	float StickTiltSlowRun = 900;		// 歩きから小走りへ変更するスティックの傾きの基準値
	float StickMargin = 50.0f;			// スティックの傾きに使用するマージン
	float Accel = 0.03f;				// 移動加速度
	float Decel = 0.1f;				// 移動減速度
	float AngleSpeed = 0.2f;			// 移動時のモデル回転速度
	float lockOnRange = 60.0f;			// ロックオン可能距離
	float HitRadius = 3.0f;				// 当たり判定半径
	float HitHeight = 16.5f;			// 当たり判定高さ
	VECTOR InitPos = { 0.0f,0.0f,0.0f };	// 初期座標
};

// アニメーション番号
enum class PlayerAnimState :int
{
	None = -1,			// なし
	TPose = 0,			// 不明
	Idle = 1,			// アイドル
	Walk = 2,			// 歩き
	SlowRun = 3,        // 小走り
	Run = 4,			// ダッシュ
	RunPose = 5,		// ダッシュポーズ
	RunStop = 6,		// ストップ
	Jump = 7,			// ジャンプ
	Fall = 8,			// 落下中
	Attack1 = 9,		// 通常攻撃（1段階）
	Attack2 = 10,		// 通常攻撃（2段階）
	Attack3 = 11,		// 通常攻撃（3段階）
	AttackDash = 12,	// 走り攻撃
	RunSword = 13,		// 走り(刀を持った状態)
	AttackJump1 = 14,	// ジャンプ攻撃（1段階）
	AttackJump2 = 15,	// ジャンプ攻撃（2段階）
	DodgeBack = 17,		// 後ろ回避
};

class EnemyBase;
class PayerStateBase;
class Player :public Character
{
public:
	Player(const std::string& name) : Character(name){}
	virtual ~Player() {}

	void Init() override;
	void Load() override;
	void Update() override;
	void Draw() override;

	void ChangeState(std::shared_ptr<PlayerStateBase> a_spState);

	// フラグセッター
	void SetRunFlag(bool flag) { isRunning = flag; }
	void SetMoveFrag(bool flag) { isMove = flag; }

	// 攻撃フラグ
	void SetAttackFrag(bool flag) { isAttack = flag; }
	const bool GetIsAttack()const { return isAttack; }

	// ロックオンフラグ
	const bool GetIsLockOn() const { return isLockOn; }
	void SetIsLockOn(bool flag) { isLockOn = flag; }

	// 回避フラグ
	const bool GetIsDodge() const { return isDodge; }
	void SetIsDodge(bool flag) { isDodge = flag; }
	const float GetCurrentDodgeSpeed() const { return currentDodgeSpeed; }
	void SetDodgeSpeed(float speed) { currentDodgeSpeed = speed; }
	void ResetDodgeFrameCount() { dodgeFrameCount = 0; }

	// 装備フラグ
	const bool GetIsSwordEpuipped() const { return isSwordEquipped; }
	void SetIsSwordEquipped(bool frag) { isSwordEquipped = frag; }

	// ジャンプ
	const int GetCurrentJumpCount() const { return jumpCount; }
	void AddJumpCount();
	void ResetJumpCount();

	const float GetHitRadius() const override { return params.HitRadius; }
	const float GetHitHeight() const override { return params.HitHeight; }

	const float GetCurrentMaxSpeed()const { return currentMaxSpeed; }
	const void SetCurrentMaxSpeed(float maxSpeed) { currentMaxSpeed = maxSpeed; }

	// 手のボーン
	const MATRIX GetHandMatrix()const { return handMatrix; }
	const int GetHandBoneIndex() const { return handBoneIndex; }

	// 鞘のボーン
	const MATRIX GetSwordSocketMatrix() const { return swordSocketMatrix; }
	const int GetSwordSocketBoneIndex() const { return swordSocketBoneIndex; }

	const VECTOR GetAttackDir() const { return attackDir; }

	void SetDodgeDirection(VECTOR dir) { dodgeDir = dir; }

	const std::shared_ptr<EnemyBase> GetLockOnTarget() { return lockOnTarget; }

	void OnHitRoof() override;       // 天井に当たった時
	void OnHitFloor() override;      // 床に当たった時
	void OnFall() override;          // 落下が確定したとき

	VECTOR GetMoveInput();		// スティックによる移動ベクトルの取得
	const VECTOR GetTargetMoveDirection() const { return targetMoveDirection; }	// モデルが向くべき方向を取得

	VECTOR GetTargetDir();	// 一番近くの敵への方向ベクトル取得
	Animation animation;		// アニメーション
	const PlayerParams& GetParams() const { return params; }

private:
	StateMachine stateMachine;	// ステートマシン
	PlayerParams params;		// パラメータ

	std::shared_ptr<EnemyBase> lockOnTarget = nullptr;	// ロックオン対象

	int handBoneIndex = -1;		// 手のボーンの番号
	MATRIX handMatrix;			// 手のボーンのマトリックス

	int swordSocketBoneIndex = -1;	// 鞘のボーンの番号
	MATRIX swordSocketMatrix;		// 鞘のマトリックス

	VECTOR attackDir = { 0.0f,0.0f,0.0f };			// 攻撃の方向ベクトル
	VECTOR dodgeDir = { 0.0f,0.0f,0.0f };			// 回避の方向ベクトル

	float currentMaxSpeed = 0.0f;				// 最大移動速度
	float currentDodgeSpeed = 0.0f;				// 現在の回避速度


	int dodgeFrameCount = 0;	// 回避中のフレームカウント

	int jumpCount = 0;			// ジャンプカウンター

	bool isRunning = false;		// 走っているか
	bool isSlowRun = false;		// 小走り状態か
	bool isLockOn = false;		// ロックオン状態か
	bool isDodge = false;		// 回避中か
	bool isSwordEquipped = false;	// 剣を手に持っているか

	void Move();	// モデルの移動
	void CulcMoveSpeed();	// 移動速度の計算

	void UpdateAngle();			// モデルの角度更新
	void ToggleLockOn();		// ロックオン切り替え
	void UpdateAttackDir();		// 攻撃の方向を更新
};