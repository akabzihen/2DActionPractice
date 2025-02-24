#pragma once

#include "define.h"
#include "Singleton.h"

#include "GimmickBase.h"

class GimmickManager : public Singleton<GimmickManager> {
public:
	GimmickManager();
	virtual ~GimmickManager() {};

	void Update(float elapsed_time);

	void Render();

	GimmickBase* Create(GimmickBase::GimmickType type);  // enum‚ðˆø”‚Æ‚µ‚Ä‚à‚ç‚¤ static

private:
	GimmickBase* gimmick_list_[MAX_GIMMICK] = {};

};