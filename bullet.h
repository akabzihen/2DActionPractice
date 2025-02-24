#pragma once

#include "actor.h"

class Bullet : public Actor {
public:
	enum class BulletType : int {
		NONE = -1,

		Straight = 0,

		MAX
	};

	enum class CollisionType : int {
		NONE = -1,

		Player = 0,
		Enemy,

		MAX
	};



public:
	Bullet() {};
	virtual ~Bullet() {};

	void Create(float pos_x, float pos_y, float direction, Bullet::BulletType, Bullet::CollisionType);
	virtual void Update(float elapsed_time) override;
	virtual void Render() override;

	virtual void DebugRender() override;

	bool IsValid() const { return is_valid_; };

private:
	bool is_valid_ = false;
	float direction_ = 0;
	Bullet::BulletType bullet_type_ = Bullet::BulletType::NONE;
	Bullet::CollisionType collision_type_ = Bullet::CollisionType::NONE;
};