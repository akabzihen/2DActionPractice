#include "TestEnemy.h"

#include "define.h"
#include "DxLib.h"

#include "player.h"
#include "StageData1.h"
#include "StageData2.h"
#include "StageDataBase.h"
#include "Stage.h"
#include "StageManager.h"
#include "BulletManager.h"
#include "StateBase.h"
#include "StatePatrol.h"
#include "StateApproach.h"
#include "StateShoot.h"

void TestEnemy::Update(float elapsed_time)
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    BulletManager* bullet_manager = BulletManager::Instance();
    if (!bullet_manager) {
        return;
    }

    if (!state_) {
        state_ = new StatePatrol(this);
    };

    StateBase::EnemyState next_state_type = state_->CheckTransition();

    StateBase* next_state = nullptr;
    switch (next_state_type)
    {
    default:
    case StateBase::EnemyState::None:
        break;

    case StateBase::EnemyState::Patrol:
        next_state = new StatePatrol(this);
        break;

    case StateBase::EnemyState::Approaceh:
        next_state = new StateApproach(this);
        break;
    case StateBase::EnemyState::Shoot:
        next_state = new StateShoot(this);
        break;
    }

    if (next_state)
    {
        state_->OnLeave(next_state);
        next_state->OnEnter(state_);

        state_ = next_state;
    }

    state_->Update(elapsed_time);




    //// テストエネミーの移動
    //float move_x, move_y;

    //// 移動量の初期化
    //move_x = 0.0F;
    //move_y = 0.0F;

    ////idoling_count_++;
    ////if (idoling_count_ > 60 && direction_ == -1) {
    //    move_x -= SPEED * 0.1f;
    //    move_x_ = move_x;
    //    //idoling_count_ = 0;
    ////}

    //fall_speed_ += G;

    //// 落下速度を移動量に加える
    //move_y = fall_speed_;
    //move_y_ = move_y;
    //// 移動量に基づいてキャラクタの座標を移動
    //Move(move_x, move_y, 32);


    //shoot_interval_count_++;
    //// プレイヤーが敵の周辺に存在していたらショットを出す
    //if (shoot_interval_count_ > 60) {

    //    if ((pos_x_ - player->GetPositionX() >= CHIP_SIZE * 3 && player->GetPositionY() - pos_y_ <= CHIP_SIZE) || (player->GetPositionX() - pos_x_ >= CHIP_SIZE * 3 && player->GetPositionY() - pos_y_ <= CHIP_SIZE)) {
    //        bullet_manager->Create(pos_x_, pos_y_, direction_, Bullet::BulletType::Straight, Bullet::CollisionType::Player);
    //    }
    //    shoot_interval_count_ = 0;
    //}
}

void TestEnemy::Render()
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    if (hp_ > 0) {
        float screenX = pos_x_ - player->GetPositionX() + SCREEN_WIDTH / 2;
        float screenY = pos_y_ - player->GetPositionY() + SCREEN_HEIGHT / 2;
        DrawBox(screenX, screenY, screenX + 32, screenY + 32, GetColor(255, 255, 0), TRUE);
    }
}

void TestEnemy::DebugRender()
{
}

void TestEnemy::OnHitBullet()
{
    hp_ -= 1;
}

int TestEnemy::GetCurrentHp()
{
    return hp_;
}

float TestEnemy::DecideMoveX(float move_x)
{
    move_x_ = move_x;
    return move_x_;
}

float TestEnemy::DecideMoveY(float move_y)
{
    move_y_ = move_y;
    return move_y_;

}

float TestEnemy::ChangeFallSpeed(float fall_speed)
{
    fall_speed_ += fall_speed;
    return fall_speed_;
}

int TestEnemy::Move(float move_x, float move_y, int size)
{
    StageManager* stage_manager = StageManager::Instance();
    if (!stage_manager) {
        return -1;
    }

    Stage* stage = stage_manager->GetCurrentStage();
    if (!stage) {
        return -1;
    }

    float Dummy = 0.0F;
    float hsize;
    float MoveXBackup = move_x;
    float MoveYBackup = move_y;

    // キャラクタの左上、右上、左下、右下部分が当たり判定のある
    // マップに衝突しているか調べ、衝突していたら補正する

    // 半分のサイズを算出
    hsize = size * 0.5F;

    // まず上下移動成分だけでチェック
    {
        // 左下のチェック、もしブロックの上辺に着いていたら落下を止める
        if (stage->CheckMapHit(pos_x_ - hsize, pos_y_ + hsize, &Dummy, &move_y) == Stage::HittingSide::UpSide)
        {
            fall_speed_ = 0.0F;
        }
        // 右下のチェック、もしブロックの上辺に着いていたら落下を止める
        if (stage->CheckMapHit(pos_x_ + hsize, pos_y_ + hsize, &Dummy, &move_y) == Stage::HittingSide::UpSide)
        {
            fall_speed_ = 0.0F;
        }
        // 左上のチェック、もしブロックの下辺に当たっていたら落下させる
        if (stage->CheckMapHit(pos_x_ - hsize, pos_y_ - hsize, &Dummy, &move_y) == Stage::HittingSide::DownSide && fall_speed_ < 0.0f)
        {
            fall_speed_ *= -1.0F;
        }
        // 右上のチェック、もしブロックの下辺に当たっていたら落下させる
        if (stage->CheckMapHit(pos_x_ + hsize, pos_y_ - hsize, &Dummy, &move_y) == Stage::HittingSide::DownSide && fall_speed_ < 0.0f)
        {
            fall_speed_ *= -1.0F;
        }
    }

    // 次に左右移動成分だけでチェック
    {
        // 左下のチェック
        stage->CheckMapHit(pos_x_, pos_y_ + size, &move_x, &Dummy);

        // 右下のチェック
        stage->CheckMapHit(pos_x_ + size, pos_y_ + size, &move_x, &Dummy);

        // 左上のチェック
        stage->CheckMapHit(pos_x_, pos_y_, &move_x, &Dummy);

        // 右上のチェック
        stage->CheckMapHit(pos_x_ + size, pos_y_, &move_x, &Dummy);

        // 左右移動成分を加算
        pos_x_ += move_x;
        move_x = 0.0f;
    }

    // 最後に坂道ブロック、上下判定ブロックを含めてチェック
    {
        // 上辺のチェック、もしブロックの上辺に着いていたら落下を止める
        if (stage->CheckMapHit2(pos_x_, pos_y_ + size, &move_x, &move_y) == Stage::HittingSide::UpSide) {
            fall_speed_ = 0.0F;
        }

        // 下辺のチェック、もしブロックの下辺に着いていたら落下させる
        if (stage->CheckMapHit2(pos_x_, pos_y_, &move_x, &move_y) == Stage::HittingSide::DownSide && fall_speed_ < 0.0f) {
            fall_speed_ *= -1.0f;
        }

        // 上下移動成分を加算
        pos_y_ += move_y;
        move_y = 0.0f;
    }

    // 接地状態保存 これ以下引数要修正
    {
        StageDataBase::MapChip Chiplayer1, ChipC1, ChipR1;
        StageDataBase::MapChip Chiplayer2, ChipC2, ChipR2;

        // 足元にブロックがあるか判定
        Chiplayer1 = stage->GetChipParam2(pos_x_ - size * 0.5F, pos_y_ + size * 0.5F + 2.0F);
        ChipC1 = stage->GetChipParam2(pos_x_, pos_y_ + size * 0.5F + 2.0F);
        ChipR1 = stage->GetChipParam2(pos_x_ + size * 0.5F, pos_y_ + size * 0.5F + 2.0F);
        if (Chiplayer1 == StageDataBase::MapChip::Square || ChipC1 != StageDataBase::MapChip::Blank || ChipR1 == StageDataBase::MapChip::Square)
        {
            // ブロックがあったら接地中にする
            is_jumping_ = false;
        }
        else
        {
            // ブロックが無い場合

            // 前回ジャンプ中であったり、落下方向への速度が無い場合は無条件でジャンプ中にする
            if (is_jumping_ || MoveYBackup <= 0.0f)
            {
                // ジャンプ中にする
                is_jumping_ = true;
            }
            else
            {
                // 前回接地していて、今回接地していなかった場合、下り坂に入ったかを判定する

                // 足元周辺にブロックがあるか調べる
                Chiplayer1 = stage->GetChipParam(pos_x_ - size * 0.5f, pos_y_ + size * 0.5F);
                ChipC1 = stage->GetChipParam(pos_x_, pos_y_ + size * 0.5F);
                ChipR1 = stage->GetChipParam(pos_x_ + size * 0.5f, pos_y_ + size * 0.5F);
                Chiplayer2 = stage->GetChipParam(pos_x_ - size * 0.5f, pos_y_ + size * 0.5F + CHIP_SIZE / 2.0f);
                ChipC2 = stage->GetChipParam(pos_x_, pos_y_ + size * 0.5F + CHIP_SIZE / 2.0f);
                ChipR2 = stage->GetChipParam(pos_x_ + size * 0.5f, pos_y_ + size * 0.5F + CHIP_SIZE / 2.0f);
                if (Chiplayer1 == StageDataBase::MapChip::Square || Chiplayer1 == StageDataBase::MapChip::RightUphill || Chiplayer1 == StageDataBase::MapChip::RightDownhill || Chiplayer1 == StageDataBase::MapChip::OnlyJudgingUpsideDownsideCelling || Chiplayer1 == StageDataBase::MapChip::SlopeAssistance ||
                    Chiplayer2 == StageDataBase::MapChip::Square || Chiplayer2 == StageDataBase::MapChip::RightUphill || Chiplayer2 == StageDataBase::MapChip::RightDownhill || Chiplayer2 == StageDataBase::MapChip::OnlyJudgingUpsideDownsideCelling || Chiplayer2 == StageDataBase::MapChip::SlopeAssistance ||
                    ChipC1 == StageDataBase::MapChip::Square || ChipC1 == StageDataBase::MapChip::RightUphill || ChipC1 == StageDataBase::MapChip::RightDownhill || ChipC1 == StageDataBase::MapChip::OnlyJudgingUpsideDownsideCelling || ChipC1 == StageDataBase::MapChip::SlopeAssistance ||
                    ChipC2 == StageDataBase::MapChip::Square || ChipC2 == StageDataBase::MapChip::RightUphill || ChipC2 == StageDataBase::MapChip::RightDownhill || ChipC2 == StageDataBase::MapChip::OnlyJudgingUpsideDownsideCelling || ChipC2 == StageDataBase::MapChip::SlopeAssistance ||
                    ChipR1 == StageDataBase::MapChip::Square || ChipR1 == StageDataBase::MapChip::RightUphill || ChipR1 == StageDataBase::MapChip::RightDownhill || ChipR1 == StageDataBase::MapChip::OnlyJudgingUpsideDownsideCelling || ChipR1 == StageDataBase::MapChip::SlopeAssistance ||
                    ChipR2 == StageDataBase::MapChip::Square || ChipR2 == StageDataBase::MapChip::RightUphill || ChipR2 == StageDataBase::MapChip::RightDownhill || ChipR2 == StageDataBase::MapChip::OnlyJudgingUpsideDownsideCelling || ChipR2 == StageDataBase::MapChip::SlopeAssistance)
                {
                    int addcy = 0;

                    // 足元周辺にブロックがあった場合は、足元のブロックに無理やり接地させる
                    if (ChipC1 != StageDataBase::MapChip::Blank || ChipC2 != StageDataBase::MapChip::Blank)
                    {
                        if (ChipC1 == StageDataBase::MapChip::Blank) {
                            addcy = 1;
                        }
                    }
                    else
                        if (Chiplayer1 != StageDataBase::MapChip::Blank || Chiplayer2 != StageDataBase::MapChip::Blank)
                        {
                            if (Chiplayer1 == StageDataBase::MapChip::Blank) {
                                addcy = 1;
                            }
                        }
                        else
                        {
                            if (ChipR1 == StageDataBase::MapChip::Blank) {
                                addcy = 1;
                            }
                        }

                    // 接地させるために無理やり足元のブロックまで移動させる
                    move_y = (((int)(pos_y_ + hsize) / CHIP_SIZE + 1 + addcy) * CHIP_SIZE - 1.0f) - (pos_y_ + hsize);
                    stage->CheckMapHit2(pos_x_, pos_y_ + hsize, &move_x, &move_y);
                    pos_y_ += move_y;
                    move_y = 0.0f;

                    // 落下速度0で接地中にする
                    fall_speed_ = 0.0F;
                    is_jumping_ = false;
                }
                else
                {
                    // 足場が無かったらジャンプ中にする
                    is_jumping_ = true;
                }
            }
        }
    }

    // 終了

    return 0;
}