#pragma once

#include "define.h"
#include "actor.h"
#include "Singleton.h"

class DebugManager : public Actor, public Singleton<DebugManager> {
public:
	DebugManager() {};
	virtual ~DebugManager() {};

	//virtual void PreUpdate(float elapsed_time);
	virtual void Update(float elapsed_time) override;
	//virtual void PostUpdate(float elapsed_time);
	virtual void Render() override;


	void DebugRender() override;



};