#include "stdafx.h"
#include "Animation.h"

void Animation::LoadAnimation(int mHandle)
{
	modelHandle = mHandle;
}

void Animation::Play(int animIndex)
{
	// HACK: 指定した番号のアニメーションをアタッチし、直前に再生していたアニメーションの情報をprevに移行している
	// 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
	if (prevPlayAnim != -1)
	{
		MV1DetachAnim(modelHandle, prevPlayAnim);
		prevPlayAnim = -1;
	}

	// 今まで再生中のモーションだったものの情報をPrevに移動する
	prevPlayAnim = currentPlayAnim;
	prevAnimCount = currentAnimCount;

	// 新たに指定のモーションをモデルにアタッチして、アタッチ番号を保存する
	currentPlayAnim = MV1AttachAnim(modelHandle, animIndex);
	currentAnimCount = 0.0f;

	// ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;
}

void Animation::Update()
{
	float animTotalTime;		// 再生しているアニメーションの総時間

	// ブレンド率が１以下の場合は１に近づける
	if (animBlendRate < 1.0f)
	{
		animBlendRate += ANIM_BLEND_SPEED;
		if (animBlendRate > 1.0f)
		{
			animBlendRate = 1.0f;
		}
	}

	// 再生しているアニメーション１の処理
	if (currentPlayAnim != -1)
	{
		// アニメーションの総時間を取得
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, currentPlayAnim);

		// 再生時間を進める
		currentAnimCount += ANIM_PLAY_SPEED;

		//	// 通常はループさせる
		if (currentAnimCount >= animTotalTime)
		{
			currentAnimCount = static_cast<float>(fmod(currentAnimCount, animTotalTime));
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(modelHandle, currentPlayAnim, currentAnimCount);

		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle, currentPlayAnim, animBlendRate);
	}

	// 再生しているアニメーション２の処理
	if (prevPlayAnim != -1)
	{
		// アニメーションの総時間を取得
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, prevPlayAnim);

		// 再生時間を進める
		prevAnimCount += ANIM_PLAY_SPEED;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (prevAnimCount > animTotalTime)
		{
			prevAnimCount = static_cast<float>(fmod(prevAnimCount, animTotalTime));
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(modelHandle, prevPlayAnim, prevAnimCount);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle, prevPlayAnim, 1.0f - animBlendRate);
	}

}