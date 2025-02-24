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

    // �`�悷��}�b�v�̊J�nX�ʒu���Z�o
    ChipStartX = ((int)player->GetPositionX() - SCREEN_WIDTH / 2) / CHIP_SIZE;
    if (ChipStartX < 0)
    {
        ChipStartX = 0;
    }

    // �`�悷��}�b�v�`�b�v�̐����Z�o
    DrawChipNum = SCREEN_WIDTH / CHIP_SIZE + 1;
    if (DrawChipNum + ChipStartX > MAP_WIDTH)
    {
        DrawChipNum = MAP_WIDTH - ChipStartX;
    }

    // �}�b�v�`�b�v�̕`��n�_���Z�o
    DrawX = SCREEN_WIDTH / 2 - (int)player->GetPositionX();
    DrawY = SCREEN_HEIGHT / 2 - (int)player->GetPositionY();

    for (i = 0; i < MAP_HEIGHT; i++)
    {
        for (j = 0; j < DrawChipNum; j++)
        {
            int ChipX;

            ChipX = j + ChipStartX;

            // �P�`�V�̓u���b�N�`�b�v��\���Ă���̂łP�`�V�̂Ƃ��낾���`��
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

                // �ǉ���������case8
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

    // �ړ��ʂ𑫂�
    afX = x + *move_x;
    afY = y + *move_y;

    // �����蔻��̂���u���b�N�ɓ������Ă��邩�`�F�b�N
    if (GetChipParam(afX, afY) == StageDataBase::MapChip::Square)
    {
        float blx, bty, brx, bby;

        // �������Ă�����ǂ��痣���������s��

        // �u���b�N�̏㉺���E�̍��W���Z�o
        blx = (float)((int)afX / CHIP_SIZE) * CHIP_SIZE;        // ���ӂ� X ���W
        brx = (float)((int)afX / CHIP_SIZE + 1) * CHIP_SIZE;    // �E�ӂ� X ���W

        bty = (float)((int)afY / CHIP_SIZE) * CHIP_SIZE;        // ��ӂ� Y ���W
        bby = (float)((int)afY / CHIP_SIZE + 1) * CHIP_SIZE;    // ���ӂ� Y ���W

        // ��ӂɓ������Ă����ꍇ
        if (*move_y > 0.0F)               // *move_y > 0.0F || *move_y < 0.0F || *move_x > 0.0F || *move_x < 0.0F
        {
            // �ړ��ʂ�␳����
            *move_y = bty - y - 1.0F;

            // ��ӂɓ��������ƕԂ�
            return Stage::HittingSide::UpSide;
        }

        // ���ӂɓ������Ă����ꍇ
        if (*move_y < 0.0F)
        {
            // �ړ��ʂ�␳����
            *move_y = bby - y + 1.0F;

            // ���ӂɓ��������ƕԂ�
            return Stage::HittingSide::DownSide;
        }

        // ���ӂɓ������Ă����ꍇ
        if (*move_x > 0.0F)
        {
            // �ړ��ʂ�␳����
            *move_x = blx - x - 1.0F;

            // ���ӂɓ��������ƕԂ�
            return Stage::HittingSide::LeftSide;
        }

        // �E�ӂɓ������Ă����ꍇ
        if (*move_x < 0.0F)
        {
            // �ړ��ʂ�␳����
            *move_x = brx - x + 1.0F;

            // �E�ӂɓ��������ƕԂ�
            return Stage::HittingSide::RightSide;
        }

        // �����ɗ�����K���Ȓl��Ԃ�
        return Stage::HittingSide::DownSide;
    }

    // �ǂ��ɂ�������Ȃ������ƕԂ�
    return Stage::HittingSide::NotHit;
}

Stage::HittingSide Stage::CheckMapHit2(float x, float y, float* move_x, float* move_y)
{
    float afX, afY;
    StageDataBase::MapChip Chip;

    // �ړ��ʂ𑫂�
    afX = x + *move_x;
    afY = y + *move_y;

    // �u���b�N�ɓ������Ă��邩�`�F�b�N
    Chip = GetChipParam(afX, afY);
    if (Chip != StageDataBase::MapChip::Blank)
    {
        float blx, bty, brx, bby;
        float blh;
        float playerx, playery;

        // �u���b�N�̏㉺���E�̍��W���Z�o
        blx = (float)((int)afX / CHIP_SIZE) * CHIP_SIZE;        // ���ӂ� X ���W
        brx = (float)((int)afX / CHIP_SIZE + 1) * CHIP_SIZE;    // �E�ӂ� X ���W

        bty = (float)((int)afY / CHIP_SIZE) * CHIP_SIZE;        // ��ӂ� Y ���W
        bby = (float)((int)afY / CHIP_SIZE + 1) * CHIP_SIZE;    // ���ӂ� Y ���W

        // �v���C���[�̈ʒu���u���b�N�̂ǂ̈ʒu�ɂ��邩�Z�o
        playerx = (afX - blx) / CHIP_SIZE;
        playery = (afY - bty) / CHIP_SIZE;

        // �⓹�⏕�u���b�N�������ꍇ�͏㉺�̍⓹�u���b�N�𔻒�Ώۂɂ���
        if (Chip == StageDataBase::MapChip::SlopeAssistance)
        {
            float addy;

            // �㉺�̋߂��u���b�N��Ώۂɂ���
            if (playery < 0.5f)
            {
                addy = -CHIP_SIZE;
            }
            else
            {
                addy = CHIP_SIZE;
            }

            // �u���b�N��蒼��
            Chip = GetChipParam(afX, afY + addy);

            // �u���b�N�̏㉺���E�̍��W���ĎZ�o
            bty = (float)((int)(afY + addy) / CHIP_SIZE) * CHIP_SIZE;        // ��ӂ� Y ���W
            bby = (float)((int)(afY + addy) / CHIP_SIZE + 1) * CHIP_SIZE;    // ���ӂ� Y ���W

            // �v���C���[�̈ʒu���u���b�N�̂ǂ̈ʒu�ɂ��邩�Z�o
            playery = (afY - bty) / CHIP_SIZE;
        }

        // �u���b�N�̃^�C�v�ɂ���ď����𕪊�
        switch (Chip)
        {
        case StageDataBase::MapChip::RightUphill:    // �E�����o��u���b�N
            // �v���C���[�̈ʒu�ł̃u���b�N�̍������Z�o
            blh = bby - playerx * CHIP_SIZE;

            // �u���b�N�ɂ������Ă����ꍇ
            if (afY > blh)
            {
                // �ړ��ʂ�␳����
                *move_y = blh - y - 1.0f;

                // ���ӂɓ��������ƕԂ�
                return Stage::HittingSide::DownSide;
            }
            break;

        case StageDataBase::MapChip::RightDownhill:    // �E��������u���b�N
            // �v���C���[�̈ʒu�ł̃u���b�N�̍������Z�o
            blh = bty + playerx * CHIP_SIZE;

            // �u���b�N�ɂ������Ă����ꍇ
            if (afY > blh)
            {
                // �ړ��ʂ�␳����
                *move_y = blh - y - 1.0f;

                // ���ӂɓ��������ƕԂ�
                return Stage::HittingSide::DownSide;
            }
            break;

        case StageDataBase::MapChip::RighthandDownCelling:    // �E��������V��u���b�N
            // �v���C���[�̈ʒu�ł̃u���b�N�̍������Z�o
            blh = bty + playerx * CHIP_SIZE;

            // �u���b�N�ɂ������Ă����ꍇ
            if (afY < blh)
            {
                // �ړ��ʂ�␳����
                *move_y = blh - y + 1.0f;

                // ��ӂɓ��������ƕԂ�
                return Stage::HittingSide::UpSide;
            }
            break;

        case StageDataBase::MapChip::RighthandUpCelling:    // �E�����o��V��u���b�N
            // �v���C���[�̈ʒu�ł̃u���b�N�̍������Z�o
            blh = bby - playerx * CHIP_SIZE;

            // �u���b�N�ɂ������Ă����ꍇ
            if (afY < blh)
            {
                // �ړ��ʂ�␳����
                *move_y = blh - y + 1.0f;

                // ��ӂɓ��������ƕԂ�
                return Stage::HittingSide::UpSide;
            }
            break;

        case StageDataBase::MapChip::Square:    // �ʏ�u���b�N
        case StageDataBase::MapChip::OnlyJudgingUpsideDownsideCelling:    // �㉺����̂݃u���b�N
            // ��ӂɓ������Ă����ꍇ
            if (*move_y > 0.0F)
            {
                // �ړ��ʂ�␳����
                *move_y = bty - y - 1.0F;

                // ���ӂɓ��������ƕԂ�
                return Stage::HittingSide::DownSide;
            }

            // ���ӂɓ������Ă����ꍇ
            if (*move_y < 0.0F)
            {
                // �ړ��ʂ�␳����
                *move_y = bby - y + 1.0F;

                // ��ӂɓ��������ƕԂ�
                return Stage::HittingSide::UpSide;
            }

            // �����ɗ�����K���Ȓl��Ԃ�
            return Stage::HittingSide::DownSide;
        }
    }

    // �ǂ��ɂ�������Ȃ������ƕԂ�
    return Stage::HittingSide::NotHit;
}

// �S�[���Ƃ̓����蔻��
Stage::HittingSide Stage::CheckMapHit3(float x, float y, float* move_x, float* move_y)
{
    Player* player = Player::Instance();
    if (!player) {
        return Stage::HittingSide::NONE;
    }

    float afX, afY;

    // �ړ��ʂ𑫂�
    afX = x + *move_x;
    afY = y + *move_y;


    // �S�[������̂���u���b�N�ɓ������Ă��邩�`�F�b�N
    if (GetChipParam(x, y) == StageDataBase::MapChip::Goal)
    {
        float blx, bty, brx, bby;


        // �u���b�N�̏㉺���E�̍��W���Z�o
        blx = (float)((int)afX / CHIP_SIZE) * CHIP_SIZE;        // ���ӂ� X ���W
        brx = (float)((int)afX / CHIP_SIZE + 1) * CHIP_SIZE;    // �E�ӂ� X ���W

        bty = (float)((int)afY / CHIP_SIZE) * CHIP_SIZE;        // ��ӂ� Y ���W
        bby = (float)((int)afY / CHIP_SIZE + 1) * CHIP_SIZE;    // ���ӂ� Y ���W

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

    // �����l�֕ϊ�
    int chip_x = (int)x / CHIP_SIZE;
    int chip_y = (int)y / CHIP_SIZE;

    // �}�b�v����͂ݏo�Ă����� 0 ��Ԃ�
    if (chip_x >= MAP_WIDTH || chip_y >= MAP_HEIGHT || chip_x < 0 || chip_y < 0)
        return StageDataBase::MapChip::Blank;

    // �w��̍��W�ɊY������}�b�v�̏���Ԃ�
    return stage_data_->GetMapData(chip_y, chip_x);
}

StageDataBase::MapChip Stage::GetChipParam2(float x, float y)
{
    StageDataBase::MapChip Chip;

    Chip = GetChipParam(x, y);

    // �⓹�u���b�N�ł͂Ȃ������炻�̂܂ܒl��Ԃ�
    if (Chip < StageDataBase::MapChip::RightUphill || Chip > StageDataBase::MapChip::SlopeAssistance)
    {
        return Chip;
    }

    // �⓹�u���b�N�̏ꍇ�͍⓹���l�����ē������Ă��邩����
    {
        float blx, bty, brx, bby;
        float blh;
        float xr, yr;

        // �u���b�N�̏㉺���E�̍��W���Z�o
        blx = (float)((int)x / CHIP_SIZE) * CHIP_SIZE;        // ���ӂ� x ���W
        brx = (float)((int)x / CHIP_SIZE + 1) * CHIP_SIZE;    // �E�ӂ� x ���W

        bty = (float)((int)y / CHIP_SIZE) * CHIP_SIZE;        // ��ӂ� y ���W
        bby = (float)((int)y / CHIP_SIZE + 1) * CHIP_SIZE;    // ���ӂ� y ���W

        // �v���C���[�̈ʒu���u���b�N�̂ǂ̈ʒu�ɂ��邩�Z�o
        xr = (x - blx) / CHIP_SIZE;
        yr = (y - bty) / CHIP_SIZE;

        // �⓹�⏕�u���b�N�������ꍇ�͏㉺�̍⓹�u���b�N�𔻒�Ώۂɂ���
        if (Chip == StageDataBase::MapChip::SlopeAssistance)
        {
            float addy;

            // �㉺�̋߂��u���b�N��Ώۂɂ���
            if (yr < 0.5f)
            {
                addy = -CHIP_SIZE;
            }
            else
            {
                addy = CHIP_SIZE;
            }

            // �u���b�N��蒼��
            Chip = GetChipParam(x, y + addy);

            // �u���b�N�̏㉺���E�̍��W���ĎZ�o
            bty = (float)((int)(y + addy) / CHIP_SIZE) * CHIP_SIZE;        // ��ӂ� y ���W
            bby = (float)((int)(y + addy) / CHIP_SIZE + 1) * CHIP_SIZE;    // ���ӂ� y ���W

            // �v���C���[�̈ʒu���u���b�N�̂ǂ̈ʒu�ɂ��邩�Z�o
            yr = (yr - bty) / CHIP_SIZE;
        }

        // �u���b�N�̃^�C�v�ɂ���ď����𕪊�
        switch (Chip)
        {
        case StageDataBase::MapChip::RightUphill:    // �E�����o��u���b�N
            // �v���C���[�̈ʒu�ł̃u���b�N�̍������Z�o
            blh = bby - xr * CHIP_SIZE;

            // �u���b�N�ɓ������Ă��邩����
            if (y > blh)
            {
                return Chip;
            }
            break;

        case StageDataBase::MapChip::RightDownhill:    // �E��������u���b�N
            // �v���C���[�̈ʒu�ł̃u���b�N�̍������Z�o
            blh = bty + xr * CHIP_SIZE;

            // �u���b�N�ɓ������Ă��邩����
            if (y > blh)
            {
                return Chip;
            }
            break;

        case StageDataBase::MapChip::RighthandDownCelling:    // �E��������V��u���b�N
            // �v���C���[�̈ʒu�ł̃u���b�N�̍������Z�o
            blh = bty + xr * CHIP_SIZE;

            // �u���b�N�ɓ������Ă��邩����
            if (y < blh)
            {
                return Chip;
            }
            break;

        case StageDataBase::MapChip::RighthandUpCelling:    // �E�����o��V��u���b�N
            // �v���C���[�̈ʒu�ł̃u���b�N�̍������Z�o
            blh = bby - xr * CHIP_SIZE;

            // �u���b�N�ɓ������Ă��邩����
            if (y < blh)
            {
                return Chip;
            }
            break;

        case StageDataBase::MapChip::OnlyJudgingUpsideDownsideCelling:    // �㉺����̂݃u���b�N
            return Chip;
        }
    }

    // �������Ă��Ȃ�������u���b�N�Ȃ��̒l��Ԃ�
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