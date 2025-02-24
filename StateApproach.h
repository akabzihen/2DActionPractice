#pragma once

#include "StateBase.h"

class StateApproach : public StateBase {
public:
    StateApproach(EnemyBase* parent);

    StateBase::EnemyState CheckTransition() override;
    void Update(float sec) override;

    void OnEnter(StateBase* prev_steta) override;
    void OnLeave(StateBase* next_state) override;

};