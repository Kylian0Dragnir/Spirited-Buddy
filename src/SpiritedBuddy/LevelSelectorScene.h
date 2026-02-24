#pragma once
#include "LevelSceneTemplate.h"

class LevelSelectorScene : public LevelSceneTemplate
{
public:
	void OnEnter() override;
	void OnUpdate(float _dt) override;
	void OnExit() override;
	void CreateCake(Vector2f _pos);
};

