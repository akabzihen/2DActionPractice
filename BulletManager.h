#pragma once

#include "Singleton.h"

#include "define.h"
#include "bullet.h"

class BulletManager : public Singleton<BulletManager> {
public:
	BulletManager() {};
	virtual ~BulletManager() {};

	void Update();

	void Render();

	void Create(float pos_x, float pos_y, float direction, Bullet::BulletType bullet_type, Bullet::CollisionType collision_type);

	void DebugRender();

private:
	int j = 0;
	Bullet shot[MAX_SHOT];
};