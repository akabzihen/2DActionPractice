#pragma once

#include "Singleton.h"

class InputManager : public Singleton<InputManager> {
public:
	InputManager() {};
	virtual ~InputManager() {};

	void Initialize();

	void Update();

	bool IsActive(unsigned int mask);
	bool IsTrigger(unsigned int mask);

private:
	int i = -1;
	int input_ = -1;
	int edge_input_ = -1;      // Åg?????Åe?
};