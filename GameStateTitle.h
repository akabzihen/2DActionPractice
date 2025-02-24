#pragma once

#include "GameStateBase.h"

class GameStateTitle : public GameStateBase {
public:
	GameStateTitle() {};
	virtual ~GameStateTitle() {};

	GameState CheckTransition() override;
	void Update(float sec) override;

	void OnEnter(GameStateBase* prev_stete) override;
	void OnLeave(GameStateBase* next_state) override;

};