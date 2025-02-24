#pragma once

class GameStateBase {
public:
	enum class GameState : int {
		None = -1,

		Title,
		Action,
		GameOver,

		MAX
	};

public:
	GameStateBase() {};
	virtual ~GameStateBase() {};

	virtual GameState CheckTransition() = 0;

	virtual void Update(float sec) = 0;

	virtual void OnEnter(GameStateBase* prev_stete) = 0;
	virtual void OnLeave(GameStateBase* next_state) = 0;

};