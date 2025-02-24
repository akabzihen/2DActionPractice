#pragma once

#include "GameStateBase.h"

class GameStateAction : public GameStateBase {
public:
	GameStateAction() {};
	virtual ~GameStateAction() {};

	GameState CheckTransition() override;
	void Update(float sec) override;

	void OnEnter(GameStateBase* prev_stete) override;
	void OnLeave(GameStateBase* next_state) override;

};