#pragma once

#include "StageDataBase.h"

class Stage {
public:
	enum class HittingSide : int {
		NONE = -1,

		NotHit = 0,
		LeftSide,
		RightSide,
		UpSide,
		DownSide,
		Goal,

		MAX
	};


public:
	Stage() {};
	~Stage() {};

	void Render();

	// �}�b�v�Ƃ̓����蔻��( �ʏ�u���b�N�Ƃ̔���̂� )
	// ( �߂�l 0:������Ȃ�����  1:���ӂɓ�������  2:�E�ӂɓ�������
	//                            3:��ӂɓ�������  4:���ӂɓ������� )
	// ���ӁFMoveX �� MoveY �A�ǂ������Е����O����Ȃ��Ƃ܂Ƃ��ɓ��삵�܂���
	HittingSide CheckMapHit(float x, float y, float* move_x, float* move_y);

	// �}�b�v�Ƃ̓����蔻��( �⓹�u���b�N�A�㉺����u���b�N�Ƃ̔�������� )
	// ( �߂�l 0:������Ȃ�����  1:��ӂɓ�������  2:���ӂɓ������� )
	HittingSide CheckMapHit2(float x, float y, float* move_x, float* move_y);

	// �S�[���Ƃ̓����蔻��
	HittingSide CheckMapHit3(float x, float y, float* move_x, float* move_y);

	// �}�b�v�`�b�v�̒l���擾����֐�
	StageDataBase::MapChip GetChipParam(float x, float y);

	// �⓹�u���b�N���l�������}�b�v�`�b�v�̒l���擾����֐�
	StageDataBase::MapChip GetChipParam2(float x, float y);

	void SetStageData(int index);

	int GetStageDataId();

private:
	StageDataBase* stage_data_ = nullptr;

};