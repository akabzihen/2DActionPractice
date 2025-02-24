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
    // �v���C���[�̍��W��������
    SetPosition(0.0F, 0.0F, 0.0F);
    direction_ = 1.f;

    // �v���C���[�̗������x��������
    down_speed_ = 0.0F;

    // �W�����v���t���O��|��
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

    // �v���C���[�̏��
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

    //// �ړ��ʂ̏�����
    //move_x = 0.0F;
    //move_y = 0.0F;

    //// ���E�̈ړ�������
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

    //// �n�ɑ��������Ă���ꍇ�̂݃W�����v�{�^��(�{�^���P or �y�L�[)������
    //if (!is_jumping_ && input_manager->IsTrigger(PAD_INPUT_A))
    //{
    //    down_speed_ = -JUMP_POWER;
    //    is_jumping_ = true;
    //}

    //// ��������
    //down_speed_ += G;

    //// �������x���ړ��ʂɉ�����
    //move_y = down_speed_;
    //move_y_ = move_y;
    //// �ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
    //Move(move_x, move_y, CHAR_SIZE);

    // �V���b�g�{�^���������Ă�����V���b�g���o�� ���v���C���[�����̂���
// ��O�̃��[�v�ŃV���b�g�{�^���������Ă�����V���b�g�͏o���Ȃ�
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


    // �L�����N�^�̕`��
    //if (hp_ > 0) {
        //DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CHAR_SIZE / 2, GetColor(255, 0, 0), TRUE);

        //���[�v���ɏ����Ȃ�
        //LoadDivGraph("C:/Users/notepad2/Documents/Visual Studio 2022/Projects/2DAction/picture/player_sample.png", 24, 4, 6, 32, 32, player_image_);
        //�A�j���[�V�����Đ��p�ϐ�

        //�摜�̕\��
        //animation_module_.PlayerRender();

        //DrawGraph(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT / 2 - 16, player_image_[Frame_], true);

        //��~��
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

    plx = (float)((pos_x_ - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // ���ӂ� X ���W
    prx = (float)((pos_x_ + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // �E�ӂ� X ���W

    pty = (float)((pos_y_ - CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;        // ��ӂ� Y ���W
    pby = (float)((pos_y_ + CHAR_SIZE / 2) / CHAR_SIZE) * CHAR_SIZE;    // ���ӂ� Y ���W

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

    // �L�����N�^�̍���A�E��A�����A�E�������������蔻��̂���
    // �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă�����␳����

    // �����̃T�C�Y���Z�o
    hsize = size * 0.5F;

    // �܂��㉺�ړ����������Ń`�F�b�N
    {
        // �����̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
        if (stage->CheckMapHit(pos_x_ - hsize, pos_y_ + hsize, &Dummy, &move_y) == Stage::HittingSide::UpSide)
        {
            down_speed_ = 0.0F;
        }
        // �E���̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
        if (stage->CheckMapHit(pos_x_ + hsize, pos_y_ + hsize, &Dummy, &move_y) == Stage::HittingSide::UpSide)
        {
            down_speed_ = 0.0F;
        }
        // ����̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
        if (stage->CheckMapHit(pos_x_ - hsize, pos_y_ - hsize, &Dummy, &move_y) == Stage::HittingSide::DownSide && down_speed_ < 0.0f)
        {
            down_speed_ *= -1.0F;
        }
        // �E��̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
        if (stage->CheckMapHit(pos_x_ + hsize, pos_y_ - hsize, &Dummy, &move_y) == Stage::HittingSide::DownSide && down_speed_ < 0.0f)
        {
            down_speed_ *= -1.0F;
        }
    }

    // ���ɍ��E�ړ����������Ń`�F�b�N
    {
        // �����̃`�F�b�N
        stage->CheckMapHit(pos_x_ - hsize, pos_y_ + hsize, &move_x, &Dummy);

        // �E���̃`�F�b�N
        stage->CheckMapHit(pos_x_ + hsize, pos_y_ + hsize, &move_x, &Dummy);

        // ����̃`�F�b�N
        stage->CheckMapHit(pos_x_ - hsize, pos_y_ - hsize, &move_x, &Dummy);

        // �E��̃`�F�b�N
        stage->CheckMapHit(pos_x_ + hsize, pos_y_ - hsize, &move_x, &Dummy);

        // ���E�ړ����������Z
        pos_x_ += move_x;
        move_x = 0.0f;
    }

    // �Ō�ɍ⓹�u���b�N�A�㉺����u���b�N���܂߂ă`�F�b�N
    {
        // ��ӂ̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
        if (stage->CheckMapHit2(pos_x_, pos_y_ + hsize, &move_x, &move_y) == Stage::HittingSide::UpSide) {
            down_speed_ = 0.0F;
        }

        // ���ӂ̃`�F�b�N�A�����u���b�N�̉��ӂɒ����Ă����痎��������
        if (stage->CheckMapHit2(pos_x_, pos_y_ - hsize, &move_x, &move_y) == Stage::HittingSide::DownSide && down_speed_ < 0.0f) {
            down_speed_ *= -1.0f;
        }

        // �㉺�ړ����������Z
        pos_y_ += move_y;
        move_y = 0.0f;
    }

    // �ڒn��ԕۑ�
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
                    down_speed_ = 0.0F;
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
