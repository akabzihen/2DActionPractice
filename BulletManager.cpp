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

    // ショットの移動処理
    for (j = 0; j < MAX_SHOT; j++)
    {
        //shot[j].(player.GetPositionX(), player.GetPositionY());
        shot[j].Update(0.f);
    }

    //// ショットボタンを押していたらショットを出す ←プレイヤーが作るのが筋
    //// 一つ前のループでショットボタンを押していたらショットは出さない
    //if (input_manager->IsTrigger(PAD_INPUT_B))
    //{
    //    // 使われていないショットデータを探す
    //    for (j = 0; j < MAX_SHOT; j++)
    //    {
    //        if (!shot[j].IsValid())
    //            break;
    //    }

    //    // もし使われていないショットデータがあったらショットを出す
    //    if (j != MAX_SHOT)
    //    {
    //        shot[j].Create(player->GetPositionX(), player->GetPositionY(), player->GetDirection(), Bullet::BulletType::Straight,Bullet::CollisionType::Enemy);
    //    }
    //}

}

void BulletManager::Render()
{
    //弾の描画
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
        // 使われていないショットデータを探す
        for (j = 0; j < MAX_SHOT; j++)
        {
            if (!shot[j].IsValid())
                break;
        }

        // もし使われていないショットデータがあったらショットを出す
        if (j != MAX_SHOT)
        {
            shot[j].Create(pos_x, pos_y, direction, bullet_type, collision_type);
        }


    case Bullet::CollisionType::Player: // プレイヤーの弾と最大数をわけたい
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