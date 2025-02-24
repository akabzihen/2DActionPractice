#include "StateApproach.h"

#include "define.h"
#include "player.h"
#include "EnemyManager.h"
#include "EnemyBase.h"

#include "TestEnemy.h"

StateApproach::StateApproach(EnemyBase* parent)
    :StateBase(parent)
{
    parent_ = parent;
}

StateBase::EnemyState StateApproach::CheckTransition()
{
    Player* player = Player::Instance();
    if (!player) {
        return EnemyState::None;
    }

    // ‹——£‚ðŒvŽZ
    float length = parent_->GetPositionX() - player->GetPositionX();

    if (length >= -96.f && 96.f < length) {
        return EnemyState::Patrol;
    }
    if (-48.f <= length && length < 48.f) {
        return EnemyState::Shoot;
    }

    return EnemyState::None;
}

void StateApproach::Update(float sec)
{
}

void StateApproach::OnEnter(StateBase* prev_steta)
{
}

void StateApproach::OnLeave(StateBase* next_state)
{
}