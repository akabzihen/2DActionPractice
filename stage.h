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

	// マップとの当たり判定( 通常ブロックとの判定のみ )
	// ( 戻り値 0:当たらなかった  1:左辺に当たった  2:右辺に当たった
	//                            3:上辺に当たった  4:下辺に当たった )
	// 注意：MoveX と MoveY 、どっちか片方が０じゃないとまともに動作しません
	HittingSide CheckMapHit(float x, float y, float* move_x, float* move_y);

	// マップとの当たり判定( 坂道ブロック、上下判定ブロックとの判定もあり )
	// ( 戻り値 0:当たらなかった  1:上辺に当たった  2:下辺に当たった )
	HittingSide CheckMapHit2(float x, float y, float* move_x, float* move_y);

	// ゴールとの当たり判定
	HittingSide CheckMapHit3(float x, float y, float* move_x, float* move_y);

	// マップチップの値を取得する関数
	StageDataBase::MapChip GetChipParam(float x, float y);

	// 坂道ブロックを考慮したマップチップの値を取得する関数
	StageDataBase::MapChip GetChipParam2(float x, float y);

	void SetStageData(int index);

	int GetStageDataId();

private:
	StageDataBase* stage_data_ = nullptr;

};