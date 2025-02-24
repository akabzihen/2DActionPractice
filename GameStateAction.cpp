#include "GameStateAction.h"

#include "define.h"
#include "DxLib.h"
#include "player.h"
#include "StageManager.h"
#include "GimmickManager.h"
#include "EnemyManager.h"

GameStateBase::GameState GameStateAction::CheckTransition()
{
    Player* player = Player::Instance();
    if (!player) {
        return GameState::None;
    }

    if (player->GetHp() <= 0) {
        return GameState::GameOver;
    }

    return GameState::None;
}

void GameStateAction::Update(float sec)
{

}

void GameStateAction::OnEnter(GameStateBase* prev_stete)
{
    StageManager* stage_manager = StageManager::Instance();
    if (!stage_manager) {
        return;
    }
    stage_manager->CreateStage();
    stage_manager->SetStageData(2);

    GimmickManager* gimmick_manager = GimmickManager::Instance();
    if (!gimmick_manager) {
        return;
    }
    GimmickBase* goal = gimmick_manager->Create(GimmickBase::GimmickType::Goal);
    if (goal) {
        goal->SetPosition(240.0F, 96.0F, 1.0F);
    }

    EnemyManager* enemy_manager = EnemyManager::Instance();
    if (!enemy_manager) {
        return;
    }
    EnemyBase* test_enemy = enemy_manager->Create(EnemyBase::EnemyType::Test);
    if (test_enemy) {
        test_enemy->SetPosition(660.0F, 408.0F, -1.F);
    }
}

void GameStateAction::OnLeave(GameStateBase* next_state)
{
}