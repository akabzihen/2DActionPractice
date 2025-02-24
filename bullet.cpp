#include "bullet.h"

#include "define.h"
#include "DxLib.h"

#include "player.h"
#include "EnemyManager.h"

void Bullet::Create(float pos_x, float pos_y, float direction, Bullet::BulletType bullet_type, Bullet::CollisionType collision_type)
{  // �V���b�g�̈ʒu��ݒ�
    pos_x_ = pos_x;
    pos_y_ = pos_y;
    direction_ = direction;
    bullet_type_ = bullet_type;
    collision_type_ = collision_type;

    // �V���b�g�f�[�^���g�p���ɃZ�b�g
    is_valid_ = true;
}

void Bullet::Update(float elapsed_time)
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    // PostUpdate��
    EnemyManager* enemy_manager = EnemyManager::Instance();
    if (!enemy_manager) {
        return;
    }

    // �V���b�g�̈ړ�����

    // �V���b�g�f�[�^��������������X�L�b�v
    if (!is_valid_) {
        return;
    }

    switch (collision_type_)
    {
    default:
    case Bullet::CollisionType::Enemy:
        // �ʒu�����E�ɂ��炷
        pos_x_ += direction_ * 8;
        break;

    case Bullet::CollisionType::Player:
        pos_x_ += direction_ * 4;
        break;
    }

    // ��ʊO�ɏo�Ă�����V���b�g�f�[�^�𖳌��ɂ���
    //if (pos_x_ < -32 || pos_x_ > 4000)
    if (pos_x_ < -32 || pos_x_ > player->GetPositionX() + 400) {
        is_valid_ = false;
    }

    // �ȉ�PostUpdate�ɏ��� �G�ƏՓ˂�����V���b�g�f�[�^�𖳌��ɂ���
    // �G�ɓ������Ă��邩�`�F�b�N

    EnemyBase** enemy_list = enemy_manager->GetEnemyList();  //�@���[�J���ϐ��Ƃ��Ď󂯎~�߂�
    if (!enemy_list) {
        return;
    }

    switch (collision_type_) {
    default:
    case Bullet::CollisionType::Enemy:
        for (int i = 0; i < MAX_ENEMY; i++) {
            if (!enemy_list[i]) {
                return;
            }
            float elx, ety, erx, eby;

            // �G�̏㉺���E�̍��W���Z�o
            elx = (float)((int)enemy_list[i]->GetPositionX() / CHIP_SIZE) * CHIP_SIZE;        // ���ӂ� X ���W
            erx = (float)((int)enemy_list[i]->GetPositionX() / CHIP_SIZE + 1) * CHIP_SIZE;    // �E�ӂ� X ���W

            ety = (float)((int)enemy_list[i]->GetPositionY() / CHIP_SIZE) * CHIP_SIZE;        // ��ӂ� Y ���W
            eby = (float)((int)enemy_list[i]->GetPositionY() / CHIP_SIZE + 1) * CHIP_SIZE;    // ���ӂ� Y ���W

            if (pos_x_ >= elx && pos_x_ <= erx && pos_y_ >= ety && pos_y_ <= eby) {
                is_valid_ = false;
                enemy_list[i]->OnHitBullet();
            }
            break;
        }
        break;

    case Bullet::CollisionType::Player:

        float plx, pty, prx, pby;

        // �v���C���[�̏㉺���E�̍��W���Z�o
        plx = (float)((player->GetPositionX() - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // ���ӂ� X ���W
        prx = (float)((player->GetPositionX() + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // �E�ӂ� X ���W

        pty = (float)((player->GetPositionY() - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // ��ӂ� Y ���W
        pby = (float)((player->GetPositionY() + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // ���ӂ� Y ���W
        //plx = (float)(((int)player->GetPositionX() - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // ���ӂ� X ���W
        //prx = (float)(((int)player->GetPositionX() + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // �E�ӂ� X ���W

        //pty = (float)(((int)player->GetPositionY() - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // ��ӂ� Y ���W
        //pby = (float)(((int)player->GetPositionY() + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // ���ӂ� Y ���W

        if (pos_x_ >= plx && pos_x_ <= prx && pos_y_ >= pty && pos_y_ <= pby) {
            is_valid_ = false;
            player->OnHitBullet();
        }
        break;
    }
}


void Bullet::Render()
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    // �V���b�g�f�[�^��������������X�L�b�v
    if (!is_valid_) {
        return;
    }


    // �V���b�g�f�[�^���L���Ȏ��̂ݕ`��
    switch (collision_type_) {
    default:
    case Bullet::CollisionType::Enemy:
        if (direction_ > 0) {
            float screenX = pos_x_ - player->GetPositionX() + SCREEN_WIDTH / 2;
            float screenY = pos_y_ - player->GetPositionY() + SCREEN_HEIGHT / 2;
            DrawBox(screenX, screenY, screenX + 8, screenY + 8, GetColor(255, 255, 255), TRUE);

        }
        if (direction_ <= 0) {
            float screenX = pos_x_ - player->GetPositionX() + SCREEN_WIDTH / 2;
            float screenY = pos_y_ - player->GetPositionY() + SCREEN_HEIGHT / 2;
            DrawBox(screenX, screenY, screenX + 8, screenY + 8, GetColor(255, 255, 255), TRUE);
        }
        break;

    case Bullet::CollisionType::Player:
        if (direction_ > 0) {
            float screenX = pos_x_ - player->GetPositionX() + SCREEN_WIDTH / 2;
            float screenY = pos_y_ - player->GetPositionY() + SCREEN_HEIGHT / 2;
            DrawBox(screenX, screenY, screenX + 8, screenY + 8, GetColor(0, 255, 255), TRUE);

        }
        if (direction_ <= 0) {
            float screenX = pos_x_ - player->GetPositionX() + SCREEN_WIDTH / 2;
            float screenY = pos_y_ - player->GetPositionY() + SCREEN_HEIGHT / 2;
            DrawBox(screenX, screenY, screenX + 8, screenY + 8, GetColor(0, 255, 255), TRUE);
        }
        break;
    }
}

void Bullet::DebugRender()
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    EnemyManager* enemy_manager = EnemyManager::Instance();
    if (!enemy_manager) {
        return;
    }

    EnemyBase** enemy_list = enemy_manager->GetEnemyList();  //�@���[�J���ϐ��Ƃ��Ď󂯎~�߂�
    if (!enemy_list) {
        return;
    }

    switch (collision_type_) {
    default:
    case Bullet::CollisionType::Enemy:
        for (int i = 0; i < MAX_ENEMY; i++) {
            if (!enemy_list[i]) {
                return;
            }
            float elx, ety, erx, eby;

            // �G�̏㉺���E�̍��W���Z�o
            elx = (float)(enemy_list[i]->GetPositionX() / CHIP_SIZE) * CHIP_SIZE;        // ���ӂ� X ���W
            erx = (float)(enemy_list[i]->GetPositionX() / CHIP_SIZE + 1) * CHIP_SIZE;    // �E�ӂ� X ���W

            ety = (float)(enemy_list[i]->GetPositionY() / CHIP_SIZE) * CHIP_SIZE;        // ��ӂ� Y ���W
            eby = (float)(enemy_list[i]->GetPositionY() / CHIP_SIZE + 1) * CHIP_SIZE;    // ���ӂ� Y ���W
            //elx = (float)((int)enemy_list[i]->GetPositionX() / CHIP_SIZE) * CHIP_SIZE;        // ���ӂ� X ���W
            //erx = (float)((int)enemy_list[i]->GetPositionX() / CHIP_SIZE + 1) * CHIP_SIZE;    // �E�ӂ� X ���W

            //ety = (float)((int)enemy_list[i]->GetPositionY() / CHIP_SIZE) * CHIP_SIZE;        // ��ӂ� Y ���W
            //eby = (float)((int)enemy_list[i]->GetPositionY() / CHIP_SIZE + 1) * CHIP_SIZE;    // ���ӂ� Y ���W

            DrawBox(elx - player->GetPositionX() + SCREEN_WIDTH / 2, ety - player->GetPositionY() + SCREEN_HEIGHT / 2, erx - player->GetPositionX() + SCREEN_WIDTH / 2, eby - player->GetPositionY() + SCREEN_HEIGHT / 2, GetColor(0, 0, 255), FALSE);
        }
        break;

    case Bullet::CollisionType::Player:
        for (int i = 0; i < MAX_ENEMY; i++) {
            if (!enemy_list[i]) {
                return;
            }

            float plx, pty, prx, pby;

            // �v���C���[�̏㉺���E�̍��W���Z�o
            plx = (float)(((int)player->GetPositionX() - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // ���ӂ� X ���W
            prx = (float)(((int)player->GetPositionX() + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // �E�ӂ� X ���W

            pty = (float)(((int)player->GetPositionY() - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // ��ӂ� Y ���W
            pby = (float)(((int)player->GetPositionY() + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // ���ӂ� Y ���W

            DrawBox(plx - player->GetPositionX() + SCREEN_WIDTH / 2, pty - player->GetPositionY() + SCREEN_HEIGHT / 2, prx - player->GetPositionX() + SCREEN_WIDTH / 2, pby - player->GetPositionY() + SCREEN_HEIGHT / 2, GetColor(0, 0, 255), FALSE);
        }
        break;
    }
}

//void Bullet::OnHitEnemy()
//{
//    is_valid_ = false;
//}
