#pragma once
#include "LevelSceneTemplate.h"

class Level2Scene : public LevelSceneTemplate
{
public:
	void OnEnter() override;
	void OnUpdate(float _dt) override;
	void OnExit() override;
};

