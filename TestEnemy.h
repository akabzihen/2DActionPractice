#pragma once

#include "EnemyBase.h"

class EnemyBase;
class StateBase;

class TestEnemy : public EnemyBase {
public:
	TestEnemy() {};
	virtual ~TestEnemy() {};

	virtual void Update(float elapsed_time) override;
	virtual void Render() override;

	virtual void DebugRender() override;

	void OnHitBullet() override;
	int GetCurrentHp() override;

	float GetFallSpeed() { return fall_speed_; };
	float DecideMoveX(float move_x);
	float DecideMoveY(float move_y);
	float ChangeFallSpeed(float fall_speed);
	void IncreaseShootIntervalCount() override { shoot_interval_count_++; };
	int GetShootIntervalCount() override { return shoot_interval_count_; };
	void ResetShootIntervalCount() override { shoot_interval_count_ = 0; }

	int GetBulletCount() { return bullet_count_; }
	void IncreaseBulletCount() { bullet_count_++; }

	//privated:
	int Move(float move_x, float move_y, int size) override;

private:
	int hp_ = 3;
	float fall_speed_ = 0.f;
	bool is_jumping_ = false;

	float move_x_ = 0.f;
	float move_y_ = 0.f;

	int idoling_count_ = 0;
	int shoot_interval_count_ = 0;
	int bullet_count_ = 0;

	StateBase* state_ = nullptr;
};