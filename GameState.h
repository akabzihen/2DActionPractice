#pragma once

#include "Singleton.h"
#include "GameStateBase.h"

class GameState : public Singleton<GameState> {
public:
	GameState() {};
	virtual ~GameState() {};

	void Update(float elapsed_time);

	GameStateBase::GameState GetCurrentState() { return current_state_; };

private:
	GameStateBase* state_ = nullptr;

	GameStateBase::GameState current_state_ = GameStateBase::GameState::None;
};