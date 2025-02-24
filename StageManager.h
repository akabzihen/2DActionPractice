#pragma once

#include "Singleton.h"

class Stage;

class StageManager : public Singleton<StageManager> {
public:
	StageManager() {};
	virtual ~StageManager() {};

	void Render();

	void CreateStage();

	void SetStageData(int index);


	Stage* GetCurrentStage() { return stage_; }

private:
	Stage* stage_ = nullptr;
};