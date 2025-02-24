#include "EnemyManager.h"

#include "EnemyBase.h"
#include "TestEnemy.h"

EnemyManager::EnemyManager()
{
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy_list_[i] = nullptr;
	}
}

void EnemyManager::Update(float elapsed_time)
{
	Delete();
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy_list_[i]) {
			continue;
		}
		enemy_list_[i]->Update(elapsed_time);
	}
}

void EnemyManager::Render()
{
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy_list_[i]) {
			continue;
		}
		enemy_list_[i]->Render();
	}
}

EnemyBase* EnemyManager::Create(EnemyBase::EnemyType type)
{
	switch (type)
	{
	default:
	case EnemyBase::EnemyType::Test:
		EnemyBase* test = new TestEnemy;
		for (int i = 0; i < MAX_ENEMY; i++) {
			if (enemy_list_[i]) {
				continue;
			}
			enemy_list_[i] = test;
			return test;
		}
		break;
	}

	return nullptr;
}

void EnemyManager::Delete()
{
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy_list_[i]) {
			continue;
		}
		if (enemy_list_[i]->GetCurrentHp() <= 0) {
			delete enemy_list_[i];
			enemy_list_[i] = nullptr;
		}
	}
}

EnemyBase** EnemyManager::GetEnemyList()
{
	return enemy_list_;
}