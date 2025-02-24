#pragma once


#include "actor.h"
#include "Singleton.h"

#include "AnimationModule.h"

class PlayerStateBase;

class Player : public Actor, public Singleton<Player> {
public:
	Player() {};
	virtual ~Player() {};

	void Initialize();
	virtual void Update(float elapsed_time) override;
	virtual void Render() override;

	virtual void DebugRender() override;


	float GetMoveX() { return move_x_; };
	float GetMoveY() { return move_y_; };
	void OnHitBullet();
	int GetHp() { return hp_; };
	float GetDownSpeed() { return down_speed_; };
	void ChangeDownSpeed(float jump_power);
	void FallingProcess();
	bool GetIsJumping() { return is_jumping_; };
	void FlagIsJumping();
	void ChangeDirection(int direction);

	//private:
	// キャラクタをマップとの当たり判定を考慮しながら移動する
	int Move(float move_x, float move_y, float size);

private:
	int hp_ = 3;
	float down_speed_ = 0.f;
	bool is_jumping_ = false;

	float move_x_ = 0.f;
	float move_y_ = 0.f;

	//static const int MaxFrame = 9;
	//const int MaxFrame = 9;
	//int Ani_image[MaxFrame];

	//int player_image_[16] ;
	//int frame_ = 0;
	//int frame_adjust_ = 0;

	AnimationModule animation_module_ = {};

	PlayerStateBase* state_ = nullptr;
};