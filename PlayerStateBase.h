#pragma once

#include "player.h"

class PlayerStateBase {
public:
	enum class PlayerState :int {
		None = -1,

		Idle,
		Walk,
		IsJumping,
		Shoot,

		MAX
	};

public:
	PlayerStateBase(Player* player) {};
	virtual ~PlayerStateBase() {};

	virtual PlayerState CheckTransition() = 0;
	virtual void Update(float sec) = 0;

	virtual void OnEnter(PlayerStateBase* prev_stete) = 0;
	virtual void OnLeave(PlayerStateBase* next_state) = 0;

private:
	PlayerStateBase() {};

protected:
	Player* player_ = nullptr;
};