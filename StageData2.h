#pragma once

#include "StageDataBase.h"

class StageData2 : public StageDataBase {
public:
	StageData2() {};
	virtual ~StageData2() {};

	virtual MapChip GetMapData(int x, int y) override;

	virtual int GetStageDataId() override;
};