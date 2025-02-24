#pragma once

class AnimationModule {
public:
	AnimationModule() {};
	virtual ~AnimationModule() {};

	void Update(float sec);
	void Render();

	void PlayAnimationIdle(int player_starting_frame, int player_last_frame);
	void PlayAnimationRightWalk();
	void PlayAnimationPlayerRightWalk(int player_starting_frame, int player_last_frame);
	void PlayAnimationPlayerLeftWalk();
	//void SetFrame(int frame);
	//void SetStartingFrame(int frame);
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
