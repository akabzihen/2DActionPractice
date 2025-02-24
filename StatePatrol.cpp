#include "StatePatrol.h"

#include "define.h"
#include "player.h"
#include "EnemyManager.h"
#include "EnemyBase.h"

#include "TestEnemy.h"


StatePatrol::StatePatrol(EnemyBase* parent)
    : StateBase(parent)
{
    parent_ = parent;
}

StateBase::EnemyState StatePatrol::CheckTransition()
{
    Player* player = Player::Instance();
    if (!player) {
        return EnemyState::None;
    }

    // �������v�Z
    float length = parent_->GetPositionX() - player->GetPositionX();
    //              ��test_enemy?

    if (-96.f < length && length < 96.f) {
        return EnemyState::Approaceh;
    }

    return EnemyState::None;
}

void StatePatrol::Update(float sec)
{

    // �e�X�g�G�l�~�[�̈ړ�
    float move_x, move_y;

    // �ړ��ʂ̏�����
    move_x = 0.0F;
    move_y = 0.0F;

    //idoling_count_++;
    //if (idoling_count_ > 60 && direction_ == -1) {
    if (parent_->GetDirection() == -1) {
        move_x -= SPEED * 0.1f;
    }
    if (parent_->GetDirection() == 1) {
        move_x += SPEED * 0.1f;
    }
    // parent_->DecideMoveX(move_x);
     //static cast ��testenemy�̃|�C���^�[�ɕς����肩��������
     //idoling_count_ = 0;
 //}
     //test_enemy->ChangeFallSpeed(G);

     // �������x���ړ��ʂɉ�����
    move_y += G;
    //test_enemy->DecideMoveY(move_y);

    // �ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
    parent_->Move(move_x, move_y, 32);

}

void StatePatrol::OnEnter(StateBase* prev_steta)
{
}

void StatePatrol::OnLeave(StateBase* next_state)
{
}