//#include "stdafx.h"
//#include "BulletFire.h"
//#include "BulletCreator.h"
//#include "Enemy.h"
//
//BulletFire::BulletFire(const std::shared_ptr<Character>& characterPtr)
//{
//	character = characterPtr;
//}
//
//void BulletFire::Init() {}
//
//void BulletFire::Update()
//{
//	if (character)
//	{
//		if (isActiveHorizontalBarrage)
//		{
//			FireHorizontalBarrage(character->GetBulletSpawnPos());
//		}
//
//		if (isActiveWaveBarrage)
//		{
//			FireWaveBarrage(character->GetBulletSpawnPos());
//		}
//	}
//}
//
//// 全方向に弾を発射
//void BulletFire::FireAllDirection(const VECTOR& pos, int bulletNum, float angleHOffset, float angleVOffset)
//{
//	// 弾の発射方向
//	VECTOR bulletFireDirection = VGet(0.0f, 0.0f, 1.0f);	// 初期値は+Z方向
//	// 角度の基準値を代入
//	bulletFireDirection = RotateFireHorizontal(bulletFireDirection, angleHOffset);
//	bulletFireDirection.y = sinf(angleVOffset);
//
//	// 弾の発射座標
//	VECTOR bulletFirePos = pos;
//	// 弾ごとの角度間隔
//	float bulletAngleDiff = DX_TWO_PI_F / bulletNum;
//
//	// 一度に発射する数だけループ
//	for (int i = 0; i < bulletNum + 1; i++)
//	{
//		// 弾を生成
//		BulletCreator::GetBulletCreator().Create(pos, bulletFireDirection);
//
//		// 角度変更
//		bulletFireDirection = RotateFireHorizontal(bulletFireDirection, bulletAngleDiff);
//	}
//}
//
//// 水平方向にのみ弾幕発射
//void BulletFire::FireHorizontalBarrage(const VECTOR& firePos)
//{
//	// フレームカウントが0かつループ回数内のみ発射
//	if (barrageFrameCount % 10 == 0 && barrageFireLoopCount <= BARRAGE_FIRE_LOOP_NUM)
//	{
//		FireAllDirection(firePos, BULLET_FIRE_ALL_DIRECTION_NUM, barrageFireAngleH, 0.0f);
//		barrageFireLoopCount++;
//		barrageFireAngleH += BARRAGE_ANGLE_H_OFFSET;
//	}
//
//	barrageFrameCount++;
//
//	if (barrageFireLoopCount == BARRAGE_FIRE_LOOP_NUM + 1)
//	{
//		isActiveHorizontalBarrage = false;
//		barrageFireLoopCount = 0;
//		barrageFireAngleH = 0;
//	}
//}
//
//// ウェーブ状の弾幕を発射
//void BulletFire::FireWaveBarrage(const VECTOR& firePos)
//{
//	// フレームカウントが0かつループ回数内のみ発射
//	if (barrageFrameCount % 10 == 0 && barrageFireLoopCount <= WAVE_BARRAGE_FIRE_LOOP_NUM)
//	{
//		// 角度を更新
//		barrageFireAngleV = (sinf(barrageFrameCount * WAVE_SPEED) + 1.0f) * 0.5f * WAVE_MAX_ANGLE_V;
//		printf("%f \n", barrageFireAngleV);
//
//		// 弾を発射
//		FireAllDirection(firePos, BULLET_FIRE_ALL_DIRECTION_NUM, barrageFireAngleH, barrageFireAngleV);
//
//		barrageFireLoopCount++;
//		barrageFireAngleH += WAVE_BARRAGE_ANGLE_H_OFFSET;
//	}
//
//	// 1フレームごとにカウント
//	barrageFrameCount++;
//
//	if (barrageFireLoopCount == WAVE_BARRAGE_FIRE_LOOP_NUM + 1)
//	{
//		isActiveWaveBarrage = false;
//		barrageFireLoopCount = 0;
//		barrageFireAngleH = 0;
//		barrageFireAngleV = 0;
//		barrageFrameCount = 0;
//	}
//}
//
//// 水平方向の回転
//VECTOR BulletFire::RotateFireHorizontal(const VECTOR& dir, float angleH)
//{
//	float cos = cosf(angleH);
//	float sin = sinf(angleH);
//
//	return VGet(
//		dir.x * cos - dir.z * sin,	// 回転後のx
//		dir.y,						// yはそのまま
//		dir.x * sin + dir.z * cos	// 回転後のz
//	);
//}
//
//
//VECTOR BulletFire::RotateFireVertical(const VECTOR& dir, float angleV)
//{
//	float cos = cosf(angleV);
//	float sin = sinf(angleV);
//
//	return VGet(
//		dir.x,
//		dir.y * cos - dir.z * sin,
//		dir.y * sin + dir.z * cos
//	);
//}