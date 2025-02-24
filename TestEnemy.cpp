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




    //// �e�X�g�G�l�~�[�̈ړ�
    //float move_x, move_y;

    //// �ړ��ʂ̏�����
    //move_x = 0.0F;
    //move_y = 0.0F;

    ////idoling_count_++;
    ////if (idoling_count_ > 60 && direction_ == -1) {
    //    move_x -= SPEED * 0.1f;
    //    move_x_ = move_x;
    //    //idoling_count_ = 0;
    ////}

    //fall_speed_ += G;

    //// �������x���ړ��ʂɉ�����
    //move_y = fall_speed_;
    //move_y_ = move_y;
    //// �ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
    //Move(move_x, move_y, 32);


    //shoot_interval_count_++;
    //// �v���C���[���G�̎��ӂɑ��݂��Ă�����V���b�g���o��
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

    // �L�����N�^�̍���A�E��A�����A�E�������������蔻��̂���
    // �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă�����␳����

    // �����̃T�C�Y���Z�o
    hsize = size * 0.5F;

    // �܂��㉺�ړ����������Ń`�F�b�N
    {
        // �����̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
        if (stage->CheckMapHit(pos_x_ - hsize, pos_y_ + hsize, &Dummy, &move_y) == Stage::HittingSide::UpSide)
        {
            fall_speed_ = 0.0F;
        }
        // �E���̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
        if (stage->CheckMapHit(pos_x_ + hsize, pos_y_ + hsize, &Dummy, &move_y) == Stage::HittingSide::UpSide)
        {
            fall_speed_ = 0.0F;
        }
        // ����̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
        if (stage->CheckMapHit(pos_x_ - hsize, pos_y_ - hsize, &Dummy, &move_y) == Stage::HittingSide::DownSide && fall_speed_ < 0.0f)
        {
            fall_speed_ *= -1.0F;
        }
        // �E��̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
        if (stage->CheckMapHit(pos_x_ + hsize, pos_y_ - hsize, &Dummy, &move_y) == Stage::HittingSide::DownSide && fall_speed_ < 0.0f)
        {
            fall_speed_ *= -1.0F;
        }
    }

    // ���ɍ��E�ړ����������Ń`�F�b�N
    {
        // �����̃`�F�b�N
        stage->CheckMapHit(pos_x_, pos_y_ + size, &move_x, &Dummy);

        // �E���̃`�F�b�N
        stage->CheckMapHit(pos_x_ + size, pos_y_ + size, &move_x, &Dummy);

        // ����̃`�F�b�N
        stage->CheckMapHit(pos_x_, pos_y_, &move_x, &Dummy);

        // �E��̃`�F�b�N
        stage->CheckMapHit(pos_x_ + size, pos_y_, &move_x, &Dummy);

        // ���E�ړ����������Z
        pos_x_ += move_x;
        move_x = 0.0f;
    }

    // �Ō�ɍ⓹�u���b�N�A�㉺����u���b�N���܂߂ă`�F�b�N
    {
        // ��ӂ̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
        if (stage->CheckMapHit2(pos_x_, pos_y_ + size, &move_x, &move_y) == Stage::HittingSide::UpSide) {
            fall_speed_ = 0.0F;
        }

        // ���ӂ̃`�F�b�N�A�����u���b�N�̉��ӂɒ����Ă����痎��������
        if (stage->CheckMapHit2(pos_x_, pos_y_, &move_x, &move_y) == Stage::HittingSide::DownSide && fall_speed_ < 0.0f) {
            fall_speed_ *= -1.0f;
        }

        // �㉺�ړ����������Z
        pos_y_ += move_y;
        move_y = 0.0f;
    }

    // �ڒn��ԕۑ� ����ȉ������v�C��
    {
        StageDataBase::MapChip Chiplayer1, ChipC1, ChipR1;
        StageDataBase::MapChip Chiplayer2, ChipC2, ChipR2;

        // �����Ƀu���b�N�����邩����
        Chiplayer1 = stage->GetChipParam2(pos_x_ - size * 0.5F, pos_y_ + size * 0.5F + 2.0F);
        ChipC1 = stage->GetChipParam2(pos_x_, pos_y_ + size * 0.5F + 2.0F);
        ChipR1 = stage->GetChipParam2(pos_x_ + size * 0.5F, pos_y_ + size * 0.5F + 2.0F);
        if (Chiplayer1 == StageDataBase::MapChip::Square || ChipC1 != StageDataBase::MapChip::Blank || ChipR1 == StageDataBase::MapChip::Square)
        {
            // �u���b�N����������ڒn���ɂ���
            is_jumping_ = false;
        }
        else
        {
            // �u���b�N�������ꍇ

            // �O��W�����v���ł�������A���������ւ̑��x�������ꍇ�͖������ŃW�����v���ɂ���
            if (is_jumping_ || MoveYBackup <= 0.0f)
            {
                // �W�����v���ɂ���
                is_jumping_ = true;
            }
            else
            {
                // �O��ڒn���Ă��āA����ڒn���Ă��Ȃ������ꍇ�A�����ɓ��������𔻒肷��

                // �������ӂɃu���b�N�����邩���ׂ�
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

                    // �������ӂɃu���b�N���������ꍇ�́A�����̃u���b�N�ɖ������ڒn������
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

                    // �ڒn�����邽�߂ɖ�����葫���̃u���b�N�܂ňړ�������
                    move_y = (((int)(pos_y_ + hsize) / CHIP_SIZE + 1 + addcy) * CHIP_SIZE - 1.0f) - (pos_y_ + hsize);
                    stage->CheckMapHit2(pos_x_, pos_y_ + hsize, &move_x, &move_y);
                    pos_y_ += move_y;
                    move_y = 0.0f;

                    // �������x0�Őڒn���ɂ���
                    fall_speed_ = 0.0F;
                    is_jumping_ = false;
                }
                else
                {
                    // ���ꂪ����������W�����v���ɂ���
                    is_jumping_ = true;
                }
            }
        }
    }

    // �I��

    return 0;
}