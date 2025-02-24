#include "bullet.h"

#include "define.h"
#include "DxLib.h"

#include "player.h"
#include "EnemyManager.h"

void Bullet::Create(float pos_x, float pos_y, float direction, Bullet::BulletType bullet_type, Bullet::CollisionType collision_type)
{  // ショットの位置を設定
    pos_x_ = pos_x;
    pos_y_ = pos_y;
    direction_ = direction;
    bullet_type_ = bullet_type;
    collision_type_ = collision_type;

    // ショットデータを使用中にセット
    is_valid_ = true;
}

void Bullet::Update(float elapsed_time)
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    // PostUpdateに
    EnemyManager* enemy_manager = EnemyManager::Instance();
    if (!enemy_manager) {
        return;
    }

    // ショットの移動処理

    // ショットデータが無効だったらスキップ
    if (!is_valid_) {
        return;
    }

    switch (collision_type_)
    {
    default:
    case Bullet::CollisionType::Enemy:
        // 位置を左右にずらす
        pos_x_ += direction_ * 8;
        break;

    case Bullet::CollisionType::Player:
        pos_x_ += direction_ * 4;
        break;
    }

    // 画面外に出ていたらショットデータを無効にする
    //if (pos_x_ < -32 || pos_x_ > 4000)
    if (pos_x_ < -32 || pos_x_ > player->GetPositionX() + 400) {
        is_valid_ = false;
    }

    // 以下PostUpdateに書く 敵と衝突したらショットデータを無効にする
    // 敵に当たっているかチェック

    EnemyBase** enemy_list = enemy_manager->GetEnemyList();  //　ローカル変数として受け止める
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

            // 敵の上下左右の座標を算出
            elx = (float)((int)enemy_list[i]->GetPositionX() / CHIP_SIZE) * CHIP_SIZE;        // 左辺の X 座標
            erx = (float)((int)enemy_list[i]->GetPositionX() / CHIP_SIZE + 1) * CHIP_SIZE;    // 右辺の X 座標

            ety = (float)((int)enemy_list[i]->GetPositionY() / CHIP_SIZE) * CHIP_SIZE;        // 上辺の Y 座標
            eby = (float)((int)enemy_list[i]->GetPositionY() / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の Y 座標

            if (pos_x_ >= elx && pos_x_ <= erx && pos_y_ >= ety && pos_y_ <= eby) {
                is_valid_ = false;
                enemy_list[i]->OnHitBullet();
            }
            break;
        }
        break;

    case Bullet::CollisionType::Player:

        float plx, pty, prx, pby;

        // プレイヤーの上下左右の座標を算出
        plx = (float)((player->GetPositionX() - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // 左辺の X 座標
        prx = (float)((player->GetPositionX() + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // 右辺の X 座標

        pty = (float)((player->GetPositionY() - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // 上辺の Y 座標
        pby = (float)((player->GetPositionY() + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // 下辺の Y 座標
        //plx = (float)(((int)player->GetPositionX() - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // 左辺の X 座標
        //prx = (float)(((int)player->GetPositionX() + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // 右辺の X 座標

        //pty = (float)(((int)player->GetPositionY() - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // 上辺の Y 座標
        //pby = (float)(((int)player->GetPositionY() + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // 下辺の Y 座標

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

    // ショットデータが無効だったらスキップ
    if (!is_valid_) {
        return;
    }


    // ショットデータが有効な時のみ描画
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

    EnemyBase** enemy_list = enemy_manager->GetEnemyList();  //　ローカル変数として受け止める
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

            // 敵の上下左右の座標を算出
            elx = (float)(enemy_list[i]->GetPositionX() / CHIP_SIZE) * CHIP_SIZE;        // 左辺の X 座標
            erx = (float)(enemy_list[i]->GetPositionX() / CHIP_SIZE + 1) * CHIP_SIZE;    // 右辺の X 座標

            ety = (float)(enemy_list[i]->GetPositionY() / CHIP_SIZE) * CHIP_SIZE;        // 上辺の Y 座標
            eby = (float)(enemy_list[i]->GetPositionY() / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の Y 座標
            //elx = (float)((int)enemy_list[i]->GetPositionX() / CHIP_SIZE) * CHIP_SIZE;        // 左辺の X 座標
            //erx = (float)((int)enemy_list[i]->GetPositionX() / CHIP_SIZE + 1) * CHIP_SIZE;    // 右辺の X 座標

            //ety = (float)((int)enemy_list[i]->GetPositionY() / CHIP_SIZE) * CHIP_SIZE;        // 上辺の Y 座標
            //eby = (float)((int)enemy_list[i]->GetPositionY() / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の Y 座標

            DrawBox(elx - player->GetPositionX() + SCREEN_WIDTH / 2, ety - player->GetPositionY() + SCREEN_HEIGHT / 2, erx - player->GetPositionX() + SCREEN_WIDTH / 2, eby - player->GetPositionY() + SCREEN_HEIGHT / 2, GetColor(0, 0, 255), FALSE);
        }
        break;

    case Bullet::CollisionType::Player:
        for (int i = 0; i < MAX_ENEMY; i++) {
            if (!enemy_list[i]) {
                return;
            }

            float plx, pty, prx, pby;

            // プレイヤーの上下左右の座標を算出
            plx = (float)(((int)player->GetPositionX() - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // 左辺の X 座標
            prx = (float)(((int)player->GetPositionX() + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // 右辺の X 座標

            pty = (float)(((int)player->GetPositionY() - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // 上辺の Y 座標
            pby = (float)(((int)player->GetPositionY() + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // 下辺の Y 座標

            DrawBox(plx - player->GetPositionX() + SCREEN_WIDTH / 2, pty - player->GetPositionY() + SCREEN_HEIGHT / 2, prx - player->GetPositionX() + SCREEN_WIDTH / 2, pby - player->GetPositionY() + SCREEN_HEIGHT / 2, GetColor(0, 0, 255), FALSE);
        }
        break;
    }
}

//void Bullet::OnHitEnemy()
//{
//    is_valid_ = false;
//}
