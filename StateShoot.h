#pragma once

#include "StateBase.h"

class StateShoot : public StateBase {
public:
    StateShoot(EnemyBase* parent);

    StateBase::EnemyState CheckTransition() override;
    void Update(float sec) override;

    void OnEnter(StateBase* prev_steta) override;
    void OnLeave(StateBase* next_state) override;

};