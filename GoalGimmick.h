#pragma once

#include "GimmickBase.h"

class StageDataBase;
class Stage;

class GoalGimmick : public GimmickBase {
public:
	GoalGimmick() {};
	virtual ~GoalGimmick() {};

	virtual void Update(float elapsed_time) override;
	virtual void Render() override;

};

// posx posy�������o
// �֐��Ƃ��ĂƂ��悤�ɂ���