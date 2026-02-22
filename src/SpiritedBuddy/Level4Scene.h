#pragma once
#include "LevelSceneTemplate.h"

class Level4Scene : public LevelSceneTemplate
{
public:
	void OnEnter() override;
	void OnUpdate(float _dt) override;
	void OnExit() override;
};