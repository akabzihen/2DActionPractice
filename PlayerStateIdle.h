#pragma once

#include "PlayerStateBase.h"
#include "AnimationModule.h"

class PlayerStateIdle : public PlayerStateBase {
public:
    PlayerStateIdle(Player* player);

    PlayerStateBase::PlayerState CheckTransition() override;
    void Update(float sec) override;

    void OnEnter(PlayerStateBase* prev_steta) override;
    void OnLeave(PlayerStateBase* next_state) override;

private:
    AnimationModule animation_module_;

};