#include "BulletManager.h"

#include "define.h"
#include "DxLib.h"

#include "InputManager.h"
#include "player.h"

void BulletManager::Update()
{
    InputManager* input_manager = InputManager::Instance();
    if (!input_manager) {
        return;
    }

    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    // �V���b�g�̈ړ�����
    for (j = 0; j < MAX_SHOT; j++)
    {
        //shot[j].(player.GetPositionX(), player.GetPositionY());
        shot[j].Update(0.f);
    }

    //// �V���b�g�{�^���������Ă�����V���b�g���o�� ���v���C���[�����̂���
    //// ��O�̃��[�v�ŃV���b�g�{�^���������Ă�����V���b�g�͏o���Ȃ�
    //if (input_manager->IsTrigger(PAD_INPUT_B))
    //{
    //    // �g���Ă��Ȃ��V���b�g�f�[�^��T��
    //    for (j = 0; j < MAX_SHOT; j++)
    //    {
    //        if (!shot[j].IsValid())
    //            break;
    //    }

    //    // �����g���Ă��Ȃ��V���b�g�f�[�^����������V���b�g���o��
    //    if (j != MAX_SHOT)
    //    {
    //        shot[j].Create(player->GetPositionX(), player->GetPositionY(), player->GetDirection(), Bullet::BulletType::Straight,Bullet::CollisionType::Enemy);
    //    }
    //}

}

void BulletManager::Render()
{
    //�e�̕`��
    for (j = 0; j < MAX_SHOT; j++)
    {
        shot[j].Render();
    }
}

void BulletManager::Create(float pos_x, float pos_y, float direction, Bullet::BulletType bullet_type, Bullet::CollisionType collision_type)
{
    switch (collision_type)
    {
    default:
    case Bullet::CollisionType::Enemy:
        // �g���Ă��Ȃ��V���b�g�f�[�^��T��
        for (j = 0; j < MAX_SHOT; j++)
        {
            if (!shot[j].IsValid())
                break;
        }

        // �����g���Ă��Ȃ��V���b�g�f�[�^����������V���b�g���o��
        if (j != MAX_SHOT)
        {
            shot[j].Create(pos_x, pos_y, direction, bullet_type, collision_type);
        }


    case Bullet::CollisionType::Player: // �v���C���[�̒e�ƍő吔���킯����
        for (j = 0; j < MAX_SHOT; j++)
        {
            if (!shot[j].IsValid())
                break;
        }

        if (j != MAX_SHOT)
        {
            shot[j].Create(pos_x, pos_y, direction, bullet_type, collision_type);
        }


    }
}

void BulletManager::DebugRender()
{
    Bullet* bullet = new Bullet;
    if (!bullet) {
        return;
    }

    bullet->DebugRender();

}