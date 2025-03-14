#include "StageData2.h"

#include <assert.h>

#include "define.h"

namespace {
    // マップデータ
    // 1 : 通常ブロック
    // 2 : 右方向登り地面ブロック
    // 3 : 右方向下り地面ブロック
    // 4 : 右方向下り天井ブロック
    // 5 : 右方向登り天井ブロック
    // 6 : 上下判定のみブロック
    // 7 : 坂道補助ブロック
    char MapData[MAP_HEIGHT][MAP_WIDTH] =
    {
        1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
        1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,1,
        1,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,0, 0,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,1,
        1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,1,
        1,0,0,0,0, 0,1,0,0,0, 0,0,0,0,0, 1,1,1,1,0, 0,0,0,0,0, 0,1,0,0,0, 0,0,0,0,0, 1,1,1,1,0, 0,0,0,0,0, 0,1,0,0,0, 0,0,0,0,0, 1,1,1,1,1,

        1,0,0,0,0, 0,0,0,1,1, 0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,1,1, 0,0,0,1,1, 1,1,1,0,1,
        1,0,0,0,0, 0,0,0,1,1, 0,0,1,1,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,1, 1,1,1,0,1,
        1,0,0,0,0, 0,0,0,0,0, 0,0,1,1,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,1,
        1,0,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
        1,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,1,0,0,0, 0,0,0,0,0, 0,0,1,1,1, 1,1,1,1,1, 1,1,0,0,0, 0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,1,

        1,0,0,0,0, 0,0,0,0,1, 0,0,0,0,0, 0,1,0,0,0, 0,0,0,0,0, 0,0,1,1,1, 1,1,1,1,1, 1,1,0,0,0, 0,0,0,0,0, 0,0,0,0,1, 0,0,0,0,0, 0,0,0,0,1,
        1,0,0,0,0, 0,0,0,1,1, 0,0,0,1,1, 1,1,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 1,1,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 0,0,0,8,8, 8,8,0,0,1,
        1,0,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 1,1,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 1,1,0,0,0, 0,0,0,1,1, 1,0,0,0,0, 0,0,0,8,8, 8,8,0,0,1,
        1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,1,1, 1,1,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
        1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
    };
}


StageDataBase::MapChip StageData2::GetMapData(int x, int y)
{
    if (x < 0 || MAP_HEIGHT <= x) {
        assert(false);
        return static_cast<StageDataBase::MapChip>(0);
    }
    if (y < 0 || MAP_WIDTH <= y) {
        assert(false);
        return MapChip::Blank;
    }

    if (MapData[x][y] <= static_cast<int>(MapChip::NONE)
        || static_cast<int>(MapChip::MAX) <= MapData[x][y])
    {
        assert(false);
        return MapChip::Blank;
    }

    return static_cast<StageDataBase::MapChip>(MapData[x][y]);
}

int StageData2::GetStageDataId()
{
    return 2;
}