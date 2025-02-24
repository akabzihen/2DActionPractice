#include "StateShoot.h"

#include "define.h"
#include "player.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "BulletManager.h"

#include "TestEnemy.h"


StateShoot::StateShoot(EnemyBase* parent)
    :StateBase(parent)
{
    parent_ = parent;
}

StateBase::EnemyState StateShoot::CheckTransition()
{
    Player* player = Player::Instance();
    if (!player) {
        return EnemyState::None;
    }

    // 距離を計算
    float length = parent_->GetPositionX() - player->GetPositionX();

    if (length >= -96.f && 96.f < length) {
        return EnemyState::Patrol;
    }

    return EnemyState::None;
}

void StateShoot::Update(float sec)
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    BulletManager* bullet_manager = BulletManager::Instance();
    if (!bullet_manager) {
        return;
    }

    parent_->IncreaseShootIntervalCount();
    //count_++;

    //// プレイヤーが敵の周辺に存在していたらショットを出す
    //if (count_ > 60) {
    //    // ↓条件Transitionに書く
    //    if ((pos_x_ - player->GetPositionX() >= CHIP_SIZE * 3 && player->GetPositionY() - pos_y_ <= CHIP_SIZE) || (player->GetPositionX() - pos_x_ >= CHIP_SIZE * 3 && player->GetPositionY() - pos_y_ <= CHIP_SIZE)) {
    //        bullet_manager->Create(pos_x_, pos_y_, direction_, Bullet::BulletType::Straight, Bullet::CollisionType::Player);
    //    }
    //    count_ = 0;
    //}
    // プレイヤーが敵の周辺に存在していたらショットを出す
    if (parent_->GetShootIntervalCount() > 60) {
        // ↓条件Transitionに書く
        //if ((pos_x_ - player->GetPositionX() >= CHIP_SIZE * 3 && player->GetPositionY() - pos_y_ <= CHIP_SIZE) || (player->GetPositionX() - pos_x_ >= CHIP_SIZE * 3 && player->GetPositionY() - pos_y_ <= CHIP_SIZE)) {
        bullet_manager->Create(parent_->GetPositionX(), parent_->GetPositionY(), parent_->GetDirection(), Bullet::BulletType::Straight, Bullet::CollisionType::Player);
        //}
        parent_->IncreaseBulletCount();
        parent_->ResetShootIntervalCount();
    }

}

void StateShoot::OnEnter(StateBase* prev_steta)
{
}

void StateShoot::OnLeave(StateBase* next_state)
{
}