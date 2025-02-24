#include "GameStateGameOver.h"

#include "define.h"
#include "DxLib.h"
#include "InputManager.h"

GameStateBase::GameState GameStateGameOver::CheckTransition()
{
    InputManager* input_manager = InputManager::Instance();
    if (!input_manager) {
        return GameState::None;
    }

    if (input_manager->IsTrigger(PAD_INPUT_10)) {
        return GameState::Title;
    }

    return GameState::None;
}

void GameStateGameOver::Update(float sec)
{
    unsigned int Color = GetColor(255, 255, 255);
    DrawString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Game Over.", Color);

}

void GameStateGameOver::OnEnter(GameStateBase* prev_stete)
{
}

void GameStateGameOver::OnLeave(GameStateBase* next_state)
{
}