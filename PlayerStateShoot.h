#pragma once

#include "PlayerStateBase.h"

class PlayerStateShoot : public PlayerStateBase {
public:
    PlayerStateShoot(Player* player);
    PlayerStateBase::PlayerState CheckTransition() override;
    void Update(float sec) override;

    void OnEnter(PlayerStateBase* prev_steta) override;
    void OnLeave(PlayerStateBase* next_state) override;

private:
    int state_count_ = 0;
};