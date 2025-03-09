#pragma once

class AnimationModule {
public:
	AnimationModule() {};
	virtual ~AnimationModule() {};

	void Update(float sec);
	void Render();

	void PlayAnimationOfPlayer(int player_starting_frame, int player_last_frame);
	
	void SetRGB(int r, int g, int b);

private:
	int player_frame_ = 0;
	int frame_adjust_ = 0;

	int player_image_[24] = {};

	int player_starting_frame_ = 0;
	int player_last_frame_ = 0;

	int r_ = 0;
	int g_ = 0;
	int b_ = 0;
};
