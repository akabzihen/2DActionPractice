#include "AnimationModule.h"

#include "DxLib.h"
#include "define.h"

void AnimationModule::Update(float sec)
{
	//‚±‚Ü‚¨‚­‚è

	if (frame_adjust_ == 8) {
		player_frame_++;
		frame_adjust_ = 0;
	}
	if (player_frame_ == 24) {
		player_frame_ = 0;
	}
	frame_adjust_++;

	//if (frame_adjust_ == 5) {
	//	player_frame_++;
	//	frame_adjust_ = 0;
	//}
	//if (player_frame_ == player_last_frame_) {
	//	player_frame_ = player_starting_frame_;
	//}
	//frame_adjust_++;


}

void AnimationModule::Render()
{
	LoadDivGraph("C:/Users/notepad2/Documents/Visual Studio 2022/Projects/2DAction/picture/player_sample.png", 24, 4, 6, 32, 32, player_image_);

	DrawGraph(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT / 2 - 16, player_image_[player_frame_], true);
	//ƒRƒ}‘—‚è‚µ‚½Œã‚Ì‚Ñ‚å‚¤‚ª‚·‚é‚¾‚¯

	//DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CHAR_SIZE / 2, GetColor(r_, g_, b_), TRUE);

}

void AnimationModule::PlayAnimationIdle(int player_starting_frame, int player_last_frame)
{
	player_starting_frame_ = player_starting_frame;

	player_frame_ = player_starting_frame_;

	player_last_frame_ = player_last_frame;

}

void AnimationModule::PlayAnimationRightWalk()
{
	// 12‚©‚ç15

}

void AnimationModule::PlayAnimationPlayerRightWalk(int player_starting_frame, int player_last_frame)
{
	// 12‚©‚ç15
	frame_adjust_ = 0;

	player_starting_frame_ = player_starting_frame;

	player_frame_ = player_starting_frame_;

	player_last_frame_ = player_last_frame;

	//LoadDivGraph("C:/Users/notepad2/Documents/Visual Studio 2022/Projects/2DAction/picture/player_sample.png", 24, 4, 6, 32, 32, player_image_);
}

void AnimationModule::PlayAnimationPlayerLeftWalk()
{
}

void AnimationModule::SetRGB(int r, int g, int b)
{
	//r_ = r;
	//g_ = g;
	//b_ = b;
}

//void AnimationModule::SetFrame(int frame)
//{
//	player_frame_ = frame;
//}
//
//void AnimationModule::SetStartingFrame(int frame)
//{
//	player_starting_frame_ = frame;
//}