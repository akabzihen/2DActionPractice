#include "StageManager.h"

#include <assert.h>

#include "stage.h"

void StageManager::Render()
{
	//GameState* game_state = GameState::Instance();
	//if (!game_state) {
	//	return;
	//}

	//if (game_state->GetCurrentState() != GameStateBase::GameState::Action) {
	//	return;
	//}


	if (!stage_) {                // stage_がnullptrの時、描画できないのでreturn
		return;
	}
	stage_->Render();
}

void StageManager::CreateStage()
{
	//GameState* game_state = GameState::Instance();
	//if (!game_state) {
	//	return;
	//}

	//if (game_state->GetCurrentState() != GameStateBase::GameState::Action) {
	//	return;
	//}


	if (stage_) {                // stage_がnullptrでない時、新しくステージを追加でつくると
		assert(false);           // おかしくなるのでassert(false)で落とす
		return;
	}
	stage_ = new Stage();
}

void StageManager::SetStageData(int index)
{
	if (!stage_) {
		return;
	}
	stage_->SetStageData(index);
}