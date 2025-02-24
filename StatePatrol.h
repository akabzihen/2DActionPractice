#pragma once

#include "StateBase.h"

class StatePatrol : public StateBase {
public:
    StatePatrol(EnemyBase* parent);

    StateBase::EnemyState CheckTransition() override;
    void Update(float sec) override;

    void OnEnter(StateBase* prev_steta) override;
    void OnLeave(StateBase* next_state) override;

};