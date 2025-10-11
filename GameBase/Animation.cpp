#include "stdafx.h"
#include "Animation.h"

void Animation::LoadAnimation(int mHandle)
{
	modelHandle = mHandle;
}

void Animation::Play(int animIndex)
{
	// HACK: �w�肵���ԍ��̃A�j���[�V�������A�^�b�`���A���O�ɍĐ����Ă����A�j���[�V�����̏���prev�Ɉڍs���Ă���
	// ����ւ����s���̂ŁA�P�O�̃��[�V���������L����������f�^�b�`����
	if (prevPlayAnim != -1)
	{
		MV1DetachAnim(modelHandle, prevPlayAnim);
		prevPlayAnim = -1;
	}

	// ���܂ōĐ����̃��[�V�������������̂̏���Prev�Ɉړ�����
	prevPlayAnim = currentPlayAnim;
	prevAnimCount = currentAnimCount;

	// �V���Ɏw��̃��[�V���������f���ɃA�^�b�`���āA�A�^�b�`�ԍ���ۑ�����
	currentPlayAnim = MV1AttachAnim(modelHandle, animIndex);
	currentAnimCount = 0.0f;

	// �u�����h����Prev���L���ł͂Ȃ��ꍇ�͂P�D�O��( ���݃��[�V�������P�O�O���̏�� )�ɂ���
	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;
}

void Animation::Update()
{
	float animTotalTime;		// �Đ����Ă���A�j���[�V�����̑�����

	// �u�����h�����P�ȉ��̏ꍇ�͂P�ɋ߂Â���
	if (animBlendRate < 1.0f)
	{
		animBlendRate += ANIM_BLEND_SPEED;
		if (animBlendRate > 1.0f)
		{
			animBlendRate = 1.0f;
		}
	}

	// �Đ����Ă���A�j���[�V�����P�̏���
	if (currentPlayAnim != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, currentPlayAnim);

		// �Đ����Ԃ�i�߂�
		currentAnimCount += ANIM_PLAY_SPEED;

		//	// �ʏ�̓��[�v������
		if (currentAnimCount >= animTotalTime)
		{
			currentAnimCount = static_cast<float>(fmod(currentAnimCount, animTotalTime));
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(modelHandle, currentPlayAnim, currentAnimCount);

		// �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(modelHandle, currentPlayAnim, animBlendRate);
	}

	// �Đ����Ă���A�j���[�V�����Q�̏���
	if (prevPlayAnim != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, prevPlayAnim);

		// �Đ����Ԃ�i�߂�
		prevAnimCount += ANIM_PLAY_SPEED;

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (prevAnimCount > animTotalTime)
		{
			prevAnimCount = static_cast<float>(fmod(prevAnimCount, animTotalTime));
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(modelHandle, prevPlayAnim, prevAnimCount);

		// �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(modelHandle, prevPlayAnim, 1.0f - animBlendRate);
	}

}