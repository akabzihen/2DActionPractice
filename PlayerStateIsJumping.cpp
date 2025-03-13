#include "PlayerStateIsJumping.h"

#include "player.h"
#include "InputManager.h"
#include "define.h"
#include "DxLib.h"

PlayerStateIsJumping::PlayerStateIsJumping(Player* player)
    :PlayerStateBase(player)
{
    player_ = player;
}

PlayerStateBase::PlayerState PlayerStateIsJumping::CheckTransition()
{
    Player* player = Player::Instance();
    if (!player) {
        return PlayerStateBase::PlayerState::None;
    }

    InputManager* input_manager = InputManager::Instance();
    if (!input_manager) {
        return PlayerStateBase::PlayerState::None;
    }

    if ((!player->GetIsJumping() && input_manager->IsActive(PAD_INPUT_LEFT)) || (!player->GetIsJumping() && input_manager->IsActive(PAD_INPUT_RIGHT))) {
        return PlayerStateBase::PlayerState::Walk;
    }

    if (!player->GetIsJumping()) {
        return PlayerStateBase::PlayerState::Idle;
    }

    return PlayerStateBase::PlayerState::None;
}

void PlayerStateIsJumping::Update(float sec)
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    InputManager* input_manager = InputManager::Instance();
    if (!input_manager) {
        return;
    }

    float move_x, move_y;

    // 移動量の初期化
    move_x = 0.0F;
    move_y = 0.0F;

    // 左右の移動を見る
    if (input_manager->IsActive(PAD_INPUT_LEFT)) {
        move_x -= SPEED;
        player->ChangeDirection(-1);
    }
    if (input_manager->IsActive(PAD_INPUT_RIGHT)) {
        move_x += SPEED;
        player->ChangeDirection(1);
    }

    player->FallingProcess();
    move_y = player->GetDownSpeed();

    player->Move(move_x, move_y, CHAR_SIZE);

    // 確認用
    //DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CHAR_SIZE / 2, GetColor(255, 0, 255), TRUE);


}

void PlayerStateIsJumping::OnEnter(PlayerStateBase* prev_steta)
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }
    InputManager* input_manager = InputManager::Instance();
    if (!input_manager) {
        return;
    }

    //player->FlagIsJumping();
    if (input_manager->IsTrigger(PAD_INPUT_A)) {
        player->ChangeDownSpeed(JUMP_POWER);
    }

    player_->GetAnimationModule()->PlayAnimationOfPlayer(4, 7);

}

void PlayerStateIsJumping::OnLeave(PlayerStateBase* next_state)
{
}