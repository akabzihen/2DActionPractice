#pragma once

#include "PlayerStateBase.h"

class PlayerStateIsJumping : public PlayerStateBase {
public:
    PlayerStateIsJumping(Player* player);

    PlayerStateBase::PlayerState CheckTransition() override;
    void Update(float sec) override;

    void OnEnter(PlayerStateBase* prev_steta) override;
    void OnLeave(PlayerStateBase* next_state) override;

};