#include "GimmickManager.h"

#include "GimmickBase.h"
#include "GoalGimmick.h"

#include "GameState.h"
#include "GameStateBase.h"

GimmickManager::GimmickManager()
{
	for (int i = 0; i < MAX_GIMMICK; i++) {
		gimmick_list_[i] = nullptr;
	}
}

void GimmickManager::Update(float elapsed_time)
{
	GameState* game_state = GameState::Instance();
	if (!game_state) {
		return;
	}

	if (game_state->GetCurrentState() != GameStateBase::GameState::Action) {
		return;
	}


	for (int i = 0; i < MAX_GIMMICK; i++) {
		if (!gimmick_list_[i]) {
			continue;
		}
		gimmick_list_[i]->Update(elapsed_time);
	}
}


void GimmickManager::Render()
{
	GameState* game_state = GameState::Instance();
	if (!game_state) {
		return;
	}

	if (game_state->GetCurrentState() != GameStateBase::GameState::Action) {
		return;
	}


	for (int i = 0; i < MAX_GIMMICK; i++) {
		if (!gimmick_list_[i]) {
			continue;
		}
		gimmick_list_[i]->Render();
	}
}

GimmickBase* GimmickManager::Create(GimmickBase::GimmickType type)
{
	switch (type)
	{
	default:
	case GimmickBase::GimmickType::Goal:
		GoalGimmick* goal = new GoalGimmick;
		for (int i = 0; i < MAX_GIMMICK; i++) {
			if (gimmick_list_[i]) {
				continue;
			}
			gimmick_list_[i] = goal;
			return goal;
		}
		break;
	}
	return nullptr;
}