#include "stage.h"

#include "define.h"
#include "DxLib.h"

#include "player.h"
#include "StageData1.h"
#include "StageData2.h"
#include "StageDataBase.h"


void Stage::Render()
{
    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    int i, j;
    int DrawX, DrawY;
    int ChipStartX;
    int DrawChipNum;

    // 描画するマップの開始X位置を算出
    ChipStartX = ((int)player->GetPositionX() - SCREEN_WIDTH / 2) / CHIP_SIZE;
    if (ChipStartX < 0)
    {
        ChipStartX = 0;
    }

    // 描画するマップチップの数を算出
    DrawChipNum = SCREEN_WIDTH / CHIP_SIZE + 1;
    if (DrawChipNum + ChipStartX > MAP_WIDTH)
    {
        DrawChipNum = MAP_WIDTH - ChipStartX;
    }

    // マップチップの描画始点を算出
    DrawX = SCREEN_WIDTH / 2 - (int)player->GetPositionX();
    DrawY = SCREEN_HEIGHT / 2 - (int)player->GetPositionY();

    for (i = 0; i < MAP_HEIGHT; i++)
    {
        for (j = 0; j < DrawChipNum; j++)
        {
            int ChipX;

            ChipX = j + ChipStartX;

            // １～７はブロックチップを表しているので１～７のところだけ描画
            switch (stage_data_->GetMapData(i, ChipX))
            {
            case StageDataBase::MapChip::Square:
            case StageDataBase::MapChip::OnlyJudgingUpsideDownsideCelling:
            case StageDataBase::MapChip::SlopeAssistance:
                DrawBox(
                    ChipX * CHIP_SIZE + DrawX, i * CHIP_SIZE + DrawY,
                    ChipX * CHIP_SIZE + DrawX + CHIP_SIZE, i * CHIP_SIZE + DrawY + CHIP_SIZE,
                    GetColor(255, 255, 255), TRUE);
                break;

                // 追加した部分case8
                //case StageDataBase::MapChip::Goal:
                //    DrawBox(
                //        ChipX * CHIP_SIZE + DrawX, i * CHIP_SIZE + DrawY,
                //        ChipX * CHIP_SIZE + DrawX + CHIP_SIZE, i * CHIP_SIZE + DrawY + CHIP_SIZE,
                //        GetColor(0, 255, 0), TRUE);
                //    break;

            case StageDataBase::MapChip::RightUphill:
                DrawTriangle(
                    ChipX * CHIP_SIZE + DrawX, i * CHIP_SIZE + DrawY + CHIP_SIZE,
                    ChipX * CHIP_SIZE + DrawX + CHIP_SIZE, i * CHIP_SIZE + DrawY,
                    ChipX * CHIP_SIZE + DrawX + CHIP_SIZE, i * CHIP_SIZE + DrawY + CHIP_SIZE,
                    GetColor(255, 255, 255), TRUE);
                break;

            case StageDataBase::MapChip::RightDownhill:
                DrawTriangle(
                    ChipX * CHIP_SIZE + DrawX, i * CHIP_SIZE + DrawY,
                    ChipX * CHIP_SIZE + DrawX + CHIP_SIZE, i * CHIP_SIZE + DrawY + CHIP_SIZE,
                    ChipX * CHIP_SIZE + DrawX, i * CHIP_SIZE + DrawY + CHIP_SIZE,
                    GetColor(255, 255, 255), TRUE);
                break;

            case StageDataBase::MapChip::RighthandDownCelling:
                DrawTriangle(
                    ChipX * CHIP_SIZE + DrawX, i * CHIP_SIZE + DrawY,
                    ChipX * CHIP_SIZE + DrawX + CHIP_SIZE, i * CHIP_SIZE + DrawY,
                    ChipX * CHIP_SIZE + DrawX + CHIP_SIZE, i * CHIP_SIZE + DrawY + CHIP_SIZE,
                    GetColor(255, 255, 255), TRUE);
                break;

            case StageDataBase::MapChip::RighthandUpCelling:
                DrawTriangle(
                    ChipX * CHIP_SIZE + DrawX, i * CHIP_SIZE + DrawY + CHIP_SIZE,
                    ChipX * CHIP_SIZE + DrawX, i * CHIP_SIZE + DrawY,
                    ChipX * CHIP_SIZE + DrawX + CHIP_SIZE, i * CHIP_SIZE + DrawY,
                    GetColor(255, 255, 255), TRUE);
                break;
            }
        }
    }

}

Stage::HittingSide Stage::CheckMapHit(float x, float y, float* move_x, float* move_y)
{
    float afX, afY;

    // 移動量を足す
    afX = x + *move_x;
    afY = y + *move_y;

    // 当たり判定のあるブロックに当たっているかチェック
    if (GetChipParam(afX, afY) == StageDataBase::MapChip::Square)
    {
        float blx, bty, brx, bby;

        // 当たっていたら壁から離す処理を行う

        // ブロックの上下左右の座標を算出
        blx = (float)((int)afX / CHIP_SIZE) * CHIP_SIZE;        // 左辺の X 座標
        brx = (float)((int)afX / CHIP_SIZE + 1) * CHIP_SIZE;    // 右辺の X 座標

        bty = (float)((int)afY / CHIP_SIZE) * CHIP_SIZE;        // 上辺の Y 座標
        bby = (float)((int)afY / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の Y 座標

        // 上辺に当たっていた場合
        if (*move_y > 0.0F)               // *move_y > 0.0F || *move_y < 0.0F || *move_x > 0.0F || *move_x < 0.0F
        {
            // 移動量を補正する
            *move_y = bty - y - 1.0F;

            // 上辺に当たったと返す
            return Stage::HittingSide::UpSide;
        }

        // 下辺に当たっていた場合
        if (*move_y < 0.0F)
        {
            // 移動量を補正する
            *move_y = bby - y + 1.0F;

            // 下辺に当たったと返す
            return Stage::HittingSide::DownSide;
        }

        // 左辺に当たっていた場合
        if (*move_x > 0.0F)
        {
            // 移動量を補正する
            *move_x = blx - x - 1.0F;

            // 左辺に当たったと返す
            return Stage::HittingSide::LeftSide;
        }

        // 右辺に当たっていた場合
        if (*move_x < 0.0F)
        {
            // 移動量を補正する
            *move_x = brx - x + 1.0F;

            // 右辺に当たったと返す
            return Stage::HittingSide::RightSide;
        }

        // ここに来たら適当な値を返す
        return Stage::HittingSide::DownSide;
    }

    // どこにも当たらなかったと返す
    return Stage::HittingSide::NotHit;
}

Stage::HittingSide Stage::CheckMapHit2(float x, float y, float* move_x, float* move_y)
{
    float afX, afY;
    StageDataBase::MapChip Chip;

    // 移動量を足す
    afX = x + *move_x;
    afY = y + *move_y;

    // ブロックに当たっているかチェック
    Chip = GetChipParam(afX, afY);
    if (Chip != StageDataBase::MapChip::Blank)
    {
        float blx, bty, brx, bby;
        float blh;
        float playerx, playery;

        // ブロックの上下左右の座標を算出
        blx = (float)((int)afX / CHIP_SIZE) * CHIP_SIZE;        // 左辺の X 座標
        brx = (float)((int)afX / CHIP_SIZE + 1) * CHIP_SIZE;    // 右辺の X 座標

        bty = (float)((int)afY / CHIP_SIZE) * CHIP_SIZE;        // 上辺の Y 座標
        bby = (float)((int)afY / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の Y 座標

        // プレイヤーの位置がブロックのどの位置にあるか算出
        playerx = (afX - blx) / CHIP_SIZE;
        playery = (afY - bty) / CHIP_SIZE;

        // 坂道補助ブロックだった場合は上下の坂道ブロックを判定対象にする
        if (Chip == StageDataBase::MapChip::SlopeAssistance)
        {
            float addy;

            // 上下の近いブロックを対象にする
            if (playery < 0.5f)
            {
                addy = -CHIP_SIZE;
            }
            else
            {
                addy = CHIP_SIZE;
            }

            // ブロック取り直し
            Chip = GetChipParam(afX, afY + addy);

            // ブロックの上下左右の座標を再算出
            bty = (float)((int)(afY + addy) / CHIP_SIZE) * CHIP_SIZE;        // 上辺の Y 座標
            bby = (float)((int)(afY + addy) / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の Y 座標

            // プレイヤーの位置がブロックのどの位置にあるか算出
            playery = (afY - bty) / CHIP_SIZE;
        }

        // ブロックのタイプによって処理を分岐
        switch (Chip)
        {
        case StageDataBase::MapChip::RightUphill:    // 右方向登りブロック
            // プレイヤーの位置でのブロックの高さを算出
            blh = bby - playerx * CHIP_SIZE;

            // ブロックにあたっていた場合
            if (afY > blh)
            {
                // 移動量を補正する
                *move_y = blh - y - 1.0f;

                // 下辺に当たったと返す
                return Stage::HittingSide::DownSide;
            }
            break;

        case StageDataBase::MapChip::RightDownhill:    // 右方向下りブロック
            // プレイヤーの位置でのブロックの高さを算出
            blh = bty + playerx * CHIP_SIZE;

            // ブロックにあたっていた場合
            if (afY > blh)
            {
                // 移動量を補正する
                *move_y = blh - y - 1.0f;

                // 下辺に当たったと返す
                return Stage::HittingSide::DownSide;
            }
            break;

        case StageDataBase::MapChip::RighthandDownCelling:    // 右方向下り天井ブロック
            // プレイヤーの位置でのブロックの高さを算出
            blh = bty + playerx * CHIP_SIZE;

            // ブロックにあたっていた場合
            if (afY < blh)
            {
                // 移動量を補正する
                *move_y = blh - y + 1.0f;

                // 上辺に当たったと返す
                return Stage::HittingSide::UpSide;
            }
            break;

        case StageDataBase::MapChip::RighthandUpCelling:    // 右方向登り天井ブロック
            // プレイヤーの位置でのブロックの高さを算出
            blh = bby - playerx * CHIP_SIZE;

            // ブロックにあたっていた場合
            if (afY < blh)
            {
                // 移動量を補正する
                *move_y = blh - y + 1.0f;

                // 上辺に当たったと返す
                return Stage::HittingSide::UpSide;
            }
            break;

        case StageDataBase::MapChip::Square:    // 通常ブロック
        case StageDataBase::MapChip::OnlyJudgingUpsideDownsideCelling:    // 上下判定のみブロック
            // 上辺に当たっていた場合
            if (*move_y > 0.0F)
            {
                // 移動量を補正する
                *move_y = bty - y - 1.0F;

                // 下辺に当たったと返す
                return Stage::HittingSide::DownSide;
            }

            // 下辺に当たっていた場合
            if (*move_y < 0.0F)
            {
                // 移動量を補正する
                *move_y = bby - y + 1.0F;

                // 上辺に当たったと返す
                return Stage::HittingSide::UpSide;
            }

            // ここに来たら適当な値を返す
            return Stage::HittingSide::DownSide;
        }
    }

    // どこにも当たらなかったと返す
    return Stage::HittingSide::NotHit;
}

// ゴールとの当たり判定
Stage::HittingSide Stage::CheckMapHit3(float x, float y, float* move_x, float* move_y)
{
    Player* player = Player::Instance();
    if (!player) {
        return Stage::HittingSide::NONE;
    }

    float afX, afY;

    // 移動量を足す
    afX = x + *move_x;
    afY = y + *move_y;


    // ゴール判定のあるブロックに当たっているかチェック
    if (GetChipParam(x, y) == StageDataBase::MapChip::Goal)
    {
        float blx, bty, brx, bby;


        // ブロックの上下左右の座標を算出
        blx = (float)((int)afX / CHIP_SIZE) * CHIP_SIZE;        // 左辺の X 座標
        brx = (float)((int)afX / CHIP_SIZE + 1) * CHIP_SIZE;    // 右辺の X 座標

        bty = (float)((int)afY / CHIP_SIZE) * CHIP_SIZE;        // 上辺の Y 座標
        bby = (float)((int)afY / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の Y 座標

        if (afX >= blx || afX <= brx || afY >= bty || afY <= bby) {
            *move_x = 0.0f;
            *move_y = 0.0f;
            return Stage::HittingSide::Goal;
        }

    }
    return Stage::HittingSide::NotHit;
}

StageDataBase::MapChip Stage::GetChipParam(float x, float y)
{

    // 整数値へ変換
    int chip_x = (int)x / CHIP_SIZE;
    int chip_y = (int)y / CHIP_SIZE;

    // マップからはみ出ていたら 0 を返す
    if (chip_x >= MAP_WIDTH || chip_y >= MAP_HEIGHT || chip_x < 0 || chip_y < 0)
        return StageDataBase::MapChip::Blank;

    // 指定の座標に該当するマップの情報を返す
    return stage_data_->GetMapData(chip_y, chip_x);
}

StageDataBase::MapChip Stage::GetChipParam2(float x, float y)
{
    StageDataBase::MapChip Chip;

    Chip = GetChipParam(x, y);

    // 坂道ブロックではなかったらそのまま値を返す
    if (Chip < StageDataBase::MapChip::RightUphill || Chip > StageDataBase::MapChip::SlopeAssistance)
    {
        return Chip;
    }

    // 坂道ブロックの場合は坂道を考慮して当たっているか判定
    {
        float blx, bty, brx, bby;
        float blh;
        float xr, yr;

        // ブロックの上下左右の座標を算出
        blx = (float)((int)x / CHIP_SIZE) * CHIP_SIZE;        // 左辺の x 座標
        brx = (float)((int)x / CHIP_SIZE + 1) * CHIP_SIZE;    // 右辺の x 座標

        bty = (float)((int)y / CHIP_SIZE) * CHIP_SIZE;        // 上辺の y 座標
        bby = (float)((int)y / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の y 座標

        // プレイヤーの位置がブロックのどの位置にあるか算出
        xr = (x - blx) / CHIP_SIZE;
        yr = (y - bty) / CHIP_SIZE;

        // 坂道補助ブロックだった場合は上下の坂道ブロックを判定対象にする
        if (Chip == StageDataBase::MapChip::SlopeAssistance)
        {
            float addy;

            // 上下の近いブロックを対象にする
            if (yr < 0.5f)
            {
                addy = -CHIP_SIZE;
            }
            else
            {
                addy = CHIP_SIZE;
            }

            // ブロック取り直し
            Chip = GetChipParam(x, y + addy);

            // ブロックの上下左右の座標を再算出
            bty = (float)((int)(y + addy) / CHIP_SIZE) * CHIP_SIZE;        // 上辺の y 座標
            bby = (float)((int)(y + addy) / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の y 座標

            // プレイヤーの位置がブロックのどの位置にあるか算出
            yr = (yr - bty) / CHIP_SIZE;
        }

        // ブロックのタイプによって処理を分岐
        switch (Chip)
        {
        case StageDataBase::MapChip::RightUphill:    // 右方向登りブロック
            // プレイヤーの位置でのブロックの高さを算出
            blh = bby - xr * CHIP_SIZE;

            // ブロックに当たっているか判定
            if (y > blh)
            {
                return Chip;
            }
            break;

        case StageDataBase::MapChip::RightDownhill:    // 右方向下りブロック
            // プレイヤーの位置でのブロックの高さを算出
            blh = bty + xr * CHIP_SIZE;

            // ブロックに当たっているか判定
            if (y > blh)
            {
                return Chip;
            }
            break;

        case StageDataBase::MapChip::RighthandDownCelling:    // 右方向下り天井ブロック
            // プレイヤーの位置でのブロックの高さを算出
            blh = bty + xr * CHIP_SIZE;

            // ブロックに当たっているか判定
            if (y < blh)
            {
                return Chip;
            }
            break;

        case StageDataBase::MapChip::RighthandUpCelling:    // 右方向登り天井ブロック
            // プレイヤーの位置でのブロックの高さを算出
            blh = bby - xr * CHIP_SIZE;

            // ブロックに当たっているか判定
            if (y < blh)
            {
                return Chip;
            }
            break;

        case StageDataBase::MapChip::OnlyJudgingUpsideDownsideCelling:    // 上下判定のみブロック
            return Chip;
        }
    }

    // 当たっていなかったらブロックなしの値を返す
    return StageDataBase::MapChip::Blank;

}

void Stage::SetStageData(int index)
{
    if (stage_data_) {
        delete stage_data_;
        stage_data_ = nullptr;
    }

    switch (index) {
    default:
    case 1:
        stage_data_ = new StageData1;
        break;
    case 2:
        stage_data_ = new StageData2;
        break;

    }
}

int Stage::GetStageDataId()
{
    if (!stage_data_) {
        return -1;
    }
    return stage_data_->GetStageDataId();
}