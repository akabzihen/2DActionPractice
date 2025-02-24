#include "GameStateTitle.h"

#include "define.h"
#include "DxLib.h"
#include "InputManager.h"

GameStateBase::GameState GameStateTitle::CheckTransition()
{
    InputManager* input_manager = InputManager::Instance();
    if (!input_manager) {
        return GameState::None;
    }

    if (input_manager->IsTrigger(PAD_INPUT_10)) {
        return GameState::Action;
    }

    return GameState::None;
}

void GameStateTitle::Update(float sec)
{
    unsigned int Color = GetColor(255, 255, 255);
    DrawString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Press SPACE KEY.", Color);
}

void GameStateTitle::OnEnter(GameStateBase* prev_stete)
{
}

void GameStateTitle::OnLeave(GameStateBase* next_state)
{
}