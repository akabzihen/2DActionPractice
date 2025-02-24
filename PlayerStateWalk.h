#pragma once

#include "PlayerStateBase.h"
#include "AnimationModule.h"

class PlayerStateWalk : public PlayerStateBase {
public:
    PlayerStateWalk(Player* player);

    PlayerStateBase::PlayerState CheckTransition() override;
    void Update(float sec) override;

    void OnEnter(PlayerStateBase* prev_steta) override;
    void OnLeave(PlayerStateBase* next_state) override;

private:
    AnimationModule animation_module_ = {};
};