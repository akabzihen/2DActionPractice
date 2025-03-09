#include "PlayerStateShoot.h"

#include "player.h"
#include "InputManager.h"
#include "BulletManager.h"
#include "define.h"
#include "DxLib.h"

PlayerStateShoot::PlayerStateShoot(Player* player)
    :PlayerStateBase(player)
{
    player_ = player;
}

PlayerStateBase::PlayerState PlayerStateShoot::CheckTransition()
{
    InputManager* input_manager = InputManager::Instance();
    if (!input_manager) {
        return PlayerStateBase::PlayerState::None;
    }

    Player* player = Player::Instance();
    if (!player) {
        return PlayerStateBase::PlayerState::None;
    }

    state_count_++;
    if (state_count_ > 30) {
        if (input_manager->IsActive(PAD_INPUT_LEFT) || input_manager->IsActive(PAD_INPUT_RIGHT)) {
            return PlayerStateBase::PlayerState::Walk;
        }

        if ((player->GetIsJumping()) || (!player->GetIsJumping() && input_manager->IsTrigger(PAD_INPUT_A))) {
            return PlayerStateBase::PlayerState::IsJumping;
        }

        if (input_manager->IsTrigger(PAD_INPUT_B)) {
            return PlayerStateBase::PlayerState::Shoot;
        }

        if ((!input_manager->IsActive(PAD_INPUT_LEFT)) && (!input_manager->IsActive(PAD_INPUT_RIGHT)) && !player->GetIsJumping()) {
            return PlayerStateBase::PlayerState::Idle;
        }
    }
    return PlayerStateBase::PlayerState::None;

}

void PlayerStateShoot::Update(float sec)
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    InputManager* input_manager = InputManager::Instance();
    if (!input_manager) {
        return;
    }

    BulletManager* bullet_manager = BulletManager::Instance();
    if (!bullet_manager) {
        return;
    }

    // �v���C���[�̌�����ύX
    if (input_manager->IsTrigger(PAD_INPUT_LEFT)) {
        player->ChangeDirection(-1);
    }
    if (input_manager->IsTrigger(PAD_INPUT_RIGHT)) {
        player->ChangeDirection(1);
    }

    float move_x, move_y;

    // �ړ��ʂ̏�����
    move_x = 0.0F;
    move_y = 0.0F;

    // ���E�̈ړ�������
    if (input_manager->IsActive(PAD_INPUT_LEFT)) {
        move_x -= SPEED;
        //player->ChangeDirection(-1);
    }
    if (input_manager->IsActive(PAD_INPUT_RIGHT)) {
        move_x += SPEED;
        //player->ChangeDirection(1);
    }

    player->FallingProcess();
    move_y = player->GetDownSpeed();

    player->Move(move_x, move_y, CHAR_SIZE);

    // �V���b�g�{�^���������Ă�����V���b�g���o�� ���v���C���[�����̂���
// ��O�̃��[�v�ŃV���b�g�{�^���������Ă�����V���b�g�͏o���Ȃ�
    if (input_manager->IsTrigger(PAD_INPUT_B)) {
        bullet_manager->Create(player->GetPositionX(), player->GetPositionY(), player->GetDirection(), Bullet::BulletType::Straight, Bullet::CollisionType::Enemy);
    }


    // �m�F�p
    //DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CHAR_SIZE / 2, GetColor(0, 0, 255), TRUE);

}

void PlayerStateShoot::OnEnter(PlayerStateBase* prev_steta)
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    InputManager* input_manager = InputManager::Instance();
    if (!input_manager) {
        return;
    }

    // �v���C���[�̌�����ύX
    if (input_manager->IsTrigger(PAD_INPUT_LEFT)) {
        player->ChangeDirection(-1);
    }
    if (input_manager->IsTrigger(PAD_INPUT_RIGHT)) {
        player->ChangeDirection(1);
    }


    // �v���C���[�̌����ɂ��Đ�����A�j���[�V������ύX
    if (player->GetDirection() == 1) {
        player_->GetAnimationModule()->PlayAnimationOfPlayer(16, 19);
    }
    if (player->GetDirection() == -1) {
        player_->GetAnimationModule()->PlayAnimationOfPlayer(20, 23);
    }

}

void PlayerStateShoot::OnLeave(PlayerStateBase* next_state)
{
}