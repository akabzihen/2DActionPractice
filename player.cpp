#include "player.h"

#include "define.h"
#include "DxLib.h"

#include "StageDataBase.h"
#include "stage.h"
#include "StageManager.h"

#include "InputManager.h"
#include "BulletManager.h"
#include "GameState.h"
#include "GameStateBase.h"

#include "PlayerStateIdle.h"
#include "PlayerStateWalk.h"
#include "PlayerStateIsJumping.h"
#include "PlayerStateShoot.h"
//#include "AnimationModule.h"


void Player::Initialize()
{
    // プレイヤーの座標を初期化
    SetPosition(0.0F, 0.0F, 0.0F);
    direction_ = 1.f;

    // プレイヤーの落下速度を初期化
    down_speed_ = 0.0F;

    // ジャンプ中フラグを倒す
    is_jumping_ = false;
}

void Player::Update(float elapsed_time)
{
    GameState* game_state = GameState::Instance();
    if (!game_state) {
        return;
    }

    if (game_state->GetCurrentState() != GameStateBase::GameState::Action) {
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

    // プレイヤーの状態
    if (!state_) {
        state_ = new PlayerStateIdle(this);
    };

    PlayerStateBase::PlayerState next_state_type = state_->CheckTransition();

    PlayerStateBase* next_state = nullptr;
    switch (next_state_type)
    {
    default:
    case PlayerStateBase::PlayerState::None:
        break;

    case PlayerStateBase::PlayerState::Idle:
        next_state = new PlayerStateIdle(this);
        break;

    case PlayerStateBase::PlayerState::Walk:
        next_state = new PlayerStateWalk(this);
        break;
    case PlayerStateBase::PlayerState::IsJumping:
        next_state = new PlayerStateIsJumping(this);
        break;
    case PlayerStateBase::PlayerState::Shoot:
        next_state = new PlayerStateShoot(this);
        break;
    }

    if (next_state)
    {
        state_->OnLeave(next_state);
        next_state->OnEnter(state_);

        state_ = next_state;
    }

    state_->Update(elapsed_time);

    //float move_x, move_y;

    //// 移動量の初期化
    //move_x = 0.0F;
    //move_y = 0.0F;

    //// 左右の移動を見る
    //if (input_manager->IsActive(PAD_INPUT_LEFT)) {
    //    move_x -= SPEED;
    //    move_x_ = move_x;
    //    direction_ = -1;
    //}
    //if (input_manager->IsActive(PAD_INPUT_RIGHT)) {
    //    move_x += SPEED;
    //    move_x_ = move_x;
    //    direction_ = 1;
    //}

    //// 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
    //if (!is_jumping_ && input_manager->IsTrigger(PAD_INPUT_A))
    //{
    //    down_speed_ = -JUMP_POWER;
    //    is_jumping_ = true;
    //}

    //// 落下処理
    //down_speed_ += G;

    //// 落下速度を移動量に加える
    //move_y = down_speed_;
    //move_y_ = move_y;
    //// 移動量に基づいてキャラクタの座標を移動
    //Move(move_x, move_y, CHAR_SIZE);

    // ショットボタンを押していたらショットを出す ←プレイヤーが作るのが筋
// 一つ前のループでショットボタンを押していたらショットは出さない
    //if (input_manager->IsTrigger(PAD_INPUT_B)) {
    //    bullet_manager->Create(pos_x_, pos_y_, direction_, Bullet::BulletType::Straight, Bullet::CollisionType::Enemy);
    //}
    animation_module_.Update(elapsed_time);
}


void Player::Render()
{
    GameState* game_state = GameState::Instance();
    if (!game_state) {
        return;
    }

    InputManager* input_manager = InputManager::Instance();
    if (!input_manager) {
        return;
    }

    if (game_state->GetCurrentState() != GameStateBase::GameState::Action) {
        return;
    }

    animation_module_.Render();


    // キャラクタの描画
    //if (hp_ > 0) {
        //DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CHAR_SIZE / 2, GetColor(255, 0, 0), TRUE);

        //ループ内に書かない
        //LoadDivGraph("C:/Users/notepad2/Documents/Visual Studio 2022/Projects/2DAction/picture/player_sample.png", 24, 4, 6, 32, 32, player_image_);
        //アニメーション再生用変数

        //画像の表示
        //animation_module_.PlayerRender();

        //DrawGraph(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT / 2 - 16, player_image_[Frame_], true);

        //停止中
        //if (direction_ = -1) {
        //    DrawGraph(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT / 2 - 16, player_image_[6], true);
        //}
        //if (direction_ = 1) {
        //    DrawGraph(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT / 2 - 16, player_image_[14], true);

        //}
        //if (input_manager->IsActive(PAD_INPUT_LEFT)) {
        //    animation_module_.Render();
        //}
        //if (input_manager->IsActive(PAD_INPUT_RIGHT)) {
        //    animation_module_.Render();
        //}
    //}
}

void Player::DebugRender()
{
    float plx, pty, prx, pby;

    plx = (float)((pos_x_ - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // 左辺の X 座標
    prx = (float)((pos_x_ + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // 右辺の X 座標

    pty = (float)((pos_y_ - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // 上辺の Y 座標
    pby = (float)((pos_y_ + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // 下辺の Y 座標

    DrawBox(plx - pos_x_ + SCREEN_WIDTH / 2, pty - pos_y_ + SCREEN_HEIGHT / 2, prx - pos_x_ + SCREEN_WIDTH / 2, pby - pos_y_ + SCREEN_HEIGHT / 2, GetColor(0, 0, 255), FALSE);

}

void Player::OnHitBullet()
{
    hp_ -= 1;
}

void Player::ChangeDownSpeed(float jump_power)
{
    down_speed_ = -jump_power;
}

void Player::FallingProcess()
{
    down_speed_ += G;
}


void Player::FlagIsJumping()
{
    is_jumping_ = true;
}

void Player::ChangeDirection(int direction)
{
    direction_ = direction;
}

int Player::Move(float move_x, float move_y, float size)
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
            down_speed_ = 0.0F;
        }
        // 右下のチェック、もしブロックの上辺に着いていたら落下を止める
        if (stage->CheckMapHit(pos_x_ + hsize, pos_y_ + hsize, &Dummy, &move_y) == Stage::HittingSide::UpSide)
        {
            down_speed_ = 0.0F;
        }
        // 左上のチェック、もしブロックの下辺に当たっていたら落下させる
        if (stage->CheckMapHit(pos_x_ - hsize, pos_y_ - hsize, &Dummy, &move_y) == Stage::HittingSide::DownSide && down_speed_ < 0.0f)
        {
            down_speed_ *= -1.0F;
        }
        // 右上のチェック、もしブロックの下辺に当たっていたら落下させる
        if (stage->CheckMapHit(pos_x_ + hsize, pos_y_ - hsize, &Dummy, &move_y) == Stage::HittingSide::DownSide && down_speed_ < 0.0f)
        {
            down_speed_ *= -1.0F;
        }
    }

    // 次に左右移動成分だけでチェック
    {
        // 左下のチェック
        stage->CheckMapHit(pos_x_ - hsize, pos_y_ + hsize, &move_x, &Dummy);

        // 右下のチェック
        stage->CheckMapHit(pos_x_ + hsize, pos_y_ + hsize, &move_x, &Dummy);

        // 左上のチェック
        stage->CheckMapHit(pos_x_ - hsize, pos_y_ - hsize, &move_x, &Dummy);

        // 右上のチェック
        stage->CheckMapHit(pos_x_ + hsize, pos_y_ - hsize, &move_x, &Dummy);

        // 左右移動成分を加算
        pos_x_ += move_x;
        move_x = 0.0f;
    }

    // 最後に坂道ブロック、上下判定ブロックを含めてチェック
    {
        // 上辺のチェック、もしブロックの上辺に着いていたら落下を止める
        if (stage->CheckMapHit2(pos_x_, pos_y_ + hsize, &move_x, &move_y) == Stage::HittingSide::UpSide) {
            down_speed_ = 0.0F;
        }

        // 下辺のチェック、もしブロックの下辺に着いていたら落下させる
        if (stage->CheckMapHit2(pos_x_, pos_y_ - hsize, &move_x, &move_y) == Stage::HittingSide::DownSide && down_speed_ < 0.0f) {
            down_speed_ *= -1.0f;
        }

        // 上下移動成分を加算
        pos_y_ += move_y;
        move_y = 0.0f;
    }

    // 接地状態保存
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
                    down_speed_ = 0.0F;
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
