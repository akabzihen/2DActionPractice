#pragma once

#include "EnemyBase.h"

class StateBase {
public:
    enum class EnemyState : int {
        None = -1,

        Patrol,
        Approaceh,
        Shoot,

        MAX
    };

public:
    StateBase(EnemyBase* parent) {};
    virtual ~StateBase() {};

    virtual EnemyState CheckTransition() = 0;
    virtual void Update(float sec) = 0;

    virtual void OnEnter(StateBase* prev_stete) = 0;
    virtual void OnLeave(StateBase* next_state) = 0;

private:
    StateBase() {};

protected:
    EnemyBase* parent_ = nullptr;
};