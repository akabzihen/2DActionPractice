#pragma once

#include "define.h"
#include "Singleton.h"

#include "EnemyBase.h"

class EnemyManager : public Singleton<EnemyManager> {
public:
	EnemyManager();
	virtual ~EnemyManager() {};

	void Update(float elapsed_time);

	void Render();

	EnemyBase* Create(EnemyBase::EnemyType type);

	void Delete();

	EnemyBase** GetEnemyList();

private:
	EnemyBase* enemy_list_[MAX_ENEMY] = {};
	EnemyBase* request_delete_list_[MAX_ENEMY] = {};

};