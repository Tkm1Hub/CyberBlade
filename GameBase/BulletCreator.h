#pragma once

class Bullet;
class BulletCreator
{
private:
	// コンストラクタを非公開にする
	BulletCreator() {}

	// コピーコンストラクタと代入演算子を削除
	BulletCreator(const BulletCreator&) = delete;
	BulletCreator& operator=(const BulletCreator&) = delete;

	// プライベートデストラクタ
	~BulletCreator() {}

public:
	// インスタンスを取得するためのメソッド
	static BulletCreator& GetBulletCreator()
	{
		static BulletCreator instance;	// 静的変数としてインスタンスを定義
		return instance;
	}

	void Init();
	void Update();
	void Create(const VECTOR& pos, const VECTOR& moveVec);
	void Draw();

	const std::vector<std::shared_ptr<Bullet>>& GetBullets() { return bullets; }

private:
	static constexpr int BULLET_NUM = 200;	// 用意する弾の数
	std::vector<std::shared_ptr<Bullet>> bullets;
};