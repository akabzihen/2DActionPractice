#pragma once

#include "StageDataBase.h"

class StageData1 : public StageDataBase {
public:
	StageData1() {};
	virtual ~StageData1() {};

	virtual MapChip GetMapData(int x, int y) override;

	virtual int GetStageDataId() override;

};