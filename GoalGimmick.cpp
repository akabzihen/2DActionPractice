#include "GoalGimmick.h"

#include "define.h"
#include "DxLib.h"

#include "player.h"
#include "StageData1.h"
#include "StageData2.h"
#include "StageDataBase.h"
#include "Stage.h"
#include "StageManager.h"
#include "GameStateBase.h"
#include "GameState.h"

void GoalGimmick::Update(float elapsed_time)
{
    GameState* game_state = GameState::Instance();
    if (!game_state) {
        return;
    }

    if (game_state->GetCurrentState() != GameStateBase::GameState::Action) {
        return;
    }


    // ゴールとの当たり判定
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    StageManager* stage_manager = StageManager::Instance();
    if (!stage_manager) {
        return;
    }

    Stage* stage = stage_manager->GetCurrentStage();
    if (!stage) {
        return;
    }


    float afX, afY;

    // 移動量を足す
    afX = player->GetPositionX() + player->GetMoveX();
    afY = player->GetPositionY() + player->GetMoveY();

    // ゴール判定のあるギミックに当たっているかチェック
    float blx, bty, brx, bby;

    // ギミックの上下左右の座標を算出
    blx = (float)((int)pos_x_ / CHIP_SIZE) * CHIP_SIZE;        // 左辺の X 座標
    brx = (float)((int)pos_x_ / CHIP_SIZE + 1) * CHIP_SIZE;    // 右辺の X 座標

    bty = (float)((int)pos_y_ / CHIP_SIZE) * CHIP_SIZE;        // 上辺の Y 座標
    bby = (float)((int)pos_y_ / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の Y 座標

    if (afX >= blx && afX <= brx && afY >= bty && afY <= bby) {
        // *move_x = 0.0f;
        // *move_y = 0.0f;
        int change_stage_index = -1;
        bool is_requested_change_stage = false;

        if (stage->GetStageDataId() == 2) {
            is_requested_change_stage = true;
            change_stage_index = 1;
        }
        else if (stage->GetStageDataId() == 1) {
            is_requested_change_stage = true;
            change_stage_index = 2;
        }

        if (is_requested_change_stage) {
            player->Initialize();
            player->SetPosition(320.0F, 240.0F, 1.0F);
            stage->SetStageData(change_stage_index);
        }

    }
    return;
    // return GimmickBase::GimmickType::Nothing;
}

void GoalGimmick::Render()
{
    GameState* game_state = GameState::Instance();
    if (!game_state) {
        return;
    }

    if (game_state->GetCurrentState() != GameStateBase::GameState::Action) {
        return;
    }


    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    float screenX = pos_x_ - player->GetPositionX() + SCREEN_WIDTH / 2;
    float screenY = pos_y_ - player->GetPositionY() + SCREEN_HEIGHT / 2;
    DrawBox(screenX, screenY, screenX + 32, screenY + 32, GetColor(0, 255, 0), TRUE);

}