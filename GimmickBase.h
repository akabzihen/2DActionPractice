#pragma once

#include "actor.h"

class GimmickBase : public Actor {
public:
	enum class GimmickType : int {
		NONE = -1,

		Nothing = 0,
		Goal,

		MAX
	};

public:
	GimmickBase() {};
	virtual  ~GimmickBase() {};

	virtual void Update(float elapsed_time) = 0;
	virtual void Render() = 0;
	void DebugRender() override;
};