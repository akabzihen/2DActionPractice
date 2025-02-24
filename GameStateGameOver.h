#pragma once

#include "GameStateBase.h"

class GameStateGameOver : public GameStateBase {
public:
	GameStateGameOver() {};
	virtual ~GameStateGameOver() {};

	GameState CheckTransition() override;
	void Update(float sec) override;

	void OnEnter(GameStateBase* prev_stete) override;
	void OnLeave(GameStateBase* next_state) override;

};