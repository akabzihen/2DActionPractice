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


	if (!stage_) {                // stage_��nullptr�̎��A�`��ł��Ȃ��̂�return
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


	if (stage_) {                // stage_��nullptr�łȂ����A�V�����X�e�[�W��ǉ��ł����
		assert(false);           // ���������Ȃ�̂�assert(false)�ŗ��Ƃ�
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