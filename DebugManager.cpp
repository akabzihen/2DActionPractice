#include "DebugManager.h"

#include "DxLib.h"
#include "InputManager.h"
#include "BulletManager.h"
#include "player.h"

void DebugManager::Update(float elapsed_time)
{
}

void DebugManager::Render()
{
}

void DebugManager::DebugRender()
{
    InputManager* input_manager = InputManager::Instance();
    if (!input_manager) {
        return;
    }

    Player* player = Player::Instance();
    if (!player) {
        return;
    }

    BulletManager* bullet_manager = BulletManager::Instance();
    if (!bullet_manager) {
        return;
    }

    if (PAD_INPUT_10) {
        bullet_manager->DebugRender();
        player->DebugRender();
    }
}