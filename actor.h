#pragma once

class Actor {
public:
	Actor() {};
	~Actor() {};
	//virtual void PreUpdate(float elapsed_time) = 0;
	virtual void Update(float elapsed_time) = 0;
	//virtual void PostUpdate(float elapsed_time) = 0;
	virtual void Render() = 0;

	virtual void DebugRender() = 0;

	void SetPosition(float x, float y, float direction);
	float GetPositionX() { return pos_x_; };
	float GetPositionY() { return pos_y_; };
	float GetDirection() { return direction_; }

protected:
	float pos_x_ = 0.f;
	float pos_y_ = 0.f;
	float direction_ = 0.f;
};