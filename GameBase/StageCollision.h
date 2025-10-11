#pragma once
#include "Character.h"
#include "GameObject.h"
class StageCollision
{
public:
	StageCollision();

	void SetStageCollision(const int collisionModelHandle);

	VECTOR CheckCollision(IGameObject& object, const VECTOR& moveVec);

private:
	static const int MaxHitColl = 2048;		// ��������R���W�����|���S���̍ő吔	
	static constexpr int HitTryNum = 32;	// �ǉ����o�������̍ő厎�s��
	static constexpr float HitSlideLength = 0.1f;	// ��x�̕ǉ����o�������ŃX���C�h�����鋗��
	static constexpr float DefaultSize = 100.0f;	// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y

	// ���o���ꂽ�|���S�����ǃ|���S��( �w�y���ʂɐ����ȃ|���S�� )�����|���S��( �w�y���ʂɐ����ł͂Ȃ��|���S�� )���𔻒f���A�ۑ�����
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);

	// �ǃ|���S���Ƃ̓�������`�F�b�N���A�␳���ׂ��ړ��x�N�g����Ԃ�
	VECTOR CheckHitWithWall(IGameObject& object, const VECTOR& checkPosition);

	// ���|���S���Ƃ̓�������`�F�b�N���A�␳���ׂ��ړ��x�N�g����Ԃ�
	VECTOR CheckHitWithFloor(IGameObject& object, const VECTOR& checkPosition);

	// HACK: �ǂ�XZ���ʂɐ����ł���O��Ő��藧���Ă���B����ȊO��u���ƃo�O��
	int		wallNum;			    // �ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
	int		floorNum;			    // ���|���S���Ɣ��f���ꂽ�|���S���̐�

	MV1_COLL_RESULT_POLY* wall[MaxHitColl];	            // �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* floor[MaxHitColl];	        // ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��

	int modelHandle = -1;
	VECTOR initPos = { 0.0f,-10.0f,10.0f };
	VECTOR modelScale = { 0.1f,0.1f,0.1f };

};