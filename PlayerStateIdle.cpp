#include "PlayerStateIdle.h"

#include "InputManager.h"
#include "player.h"
#include "define.h"
#include "DxLib.h"
#include "AnimationModule.h"

PlayerStateIdle::PlayerStateIdle(Player* player)
    :PlayerStateBase(player)
{
    player_ = player;
}

PlayerStateBase::PlayerState PlayerStateIdle::CheckTransition()
{
    InputManager* input_manager = InputManager::Instance();
    if (!input_manager) {
        return PlayerStateBase::PlayerState::None;
    }

    Player* player = Player::Instance();
    if (!player) {
        return PlayerStateBase::PlayerState::None;
    }

    if (input_manager->IsTrigger(PAD_INPUT_LEFT) || input_manager->IsTrigger(PAD_INPUT_RIGHT)) {
        return PlayerStateBase::PlayerState::Walk;
    }

    if ((player->GetIsJumping()) || (!player->GetIsJumping() && input_manager->IsTrigger(PAD_INPUT_A))) {
        return PlayerStateBase::PlayerState::IsJumping;
    }

    if (input_manager->IsTrigger(PAD_INPUT_B)) {
        return PlayerStateBase::PlayerState::Shoot;
    }
    return PlayerStateBase::PlayerState::None;
}

void PlayerStateIdle::Update(float sec)
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
    //if (input_manager->IsActive(PAD_INPUT_LEFT)) {
    //    move_x -= SPEED;
    //    player->ChangeDirection(-1);
    //}
    //if (input_manager->IsActive(PAD_INPUT_RIGHT)) {
    //    move_x += SPEED;
    //    player->ChangeDirection(1);
    //}

    //player->FallingProcess();
    //move_y = player->GetDownSpeed();

    player->Move(move_x, move_y, CHAR_SIZE);

    animation_module_.Update(sec);
    // 確認用
    //DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CHAR_SIZE / 2, GetColor(255, 0, 0), TRUE);


}

void PlayerStateIdle::OnEnter(PlayerStateBase* prev_steta)
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    //InputManager* input_manager = InputManager::Instance();
    //if (!input_manager) {
    //    return;
    //}

    //// プレイヤーの向きを変更
    //if (input_manager->IsTrigger(PAD_INPUT_LEFT)) {
    //    player->ChangeDirection(-1);
    //}
    //if (input_manager->IsTrigger(PAD_INPUT_RIGHT)) {
    //    player->ChangeDirection(1);
    //}


    // プレイヤーの向きにより再生するアニメーションを変更
    if (player->GetDirection() == 1) {
        player_->GetAnimationModule()->PlayAnimationOfPlayer(0, 1);
    }
    if (player->GetDirection() == -1) {
        player_->GetAnimationModule()->PlayAnimationOfPlayer(2, 3);
    }

}

void PlayerStateIdle::OnLeave(PlayerStateBase* next_state)
{
}