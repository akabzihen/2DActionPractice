#include "GameState.h"

#include "GameStateBase.h"
#include "GameStateTitle.h"
#include "GameStateAction.h"
#include "GameStateGameOver.h"

void GameState::Update(float elapsed_time)
{
    if (!state_) {
        state_ = new GameStateTitle;
    }

    GameStateBase::GameState next_state_type = state_->CheckTransition();

    GameStateBase* next_state = nullptr;

    switch (next_state_type)
    {
    default:
    case GameStateBase::GameState::None:
        break;

    case GameStateBase::GameState::Title:
        next_state = new GameStateTitle;
        current_state_ = GameStateBase::GameState::Title;
        break;

    case GameStateBase::GameState::Action:
        next_state = new GameStateAction;
        current_state_ = GameStateBase::GameState::Action;

        break;
    case GameStateBase::GameState::GameOver:
        next_state = new GameStateGameOver;
        current_state_ = GameStateBase::GameState::GameOver;

        break;
    }

    if (next_state)
    {
        state_->OnLeave(next_state);
        next_state->OnEnter(state_);

        state_ = next_state;
    }

    state_->Update(elapsed_time);

}