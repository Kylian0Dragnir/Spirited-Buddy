#pragma once
#include "LevelSceneTemplate.h"

class LevelTestScene : public LevelSceneTemplate
{
public:
	void OnEnter() override;
	void OnUpdate(float _dt) override;
	void OnExit() override;
};

