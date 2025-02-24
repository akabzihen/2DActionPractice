#pragma once

#include "actor.h"

class EnemyBase : public Actor {
public:
	enum class EnemyType : int {
		NONE = -1,

		Nothing = 0,
		Test,

		MAX
	};

public:
	EnemyBase() {};
	virtual  ~EnemyBase() {};

	virtual void Update(float elapsed_time) = 0;
	virtual void Render() = 0;
	virtual void OnHitBullet() = 0;
	virtual int GetCurrentHp() = 0;
	virtual int Move(float move_x, float move_y, int size) = 0;
	virtual void IncreaseShootIntervalCount() = 0;
	virtual int GetShootIntervalCount() = 0;
	virtual void ResetShootIntervalCount() = 0;
	virtual void IncreaseBulletCount() = 0;

	void DebugRender() override;
};