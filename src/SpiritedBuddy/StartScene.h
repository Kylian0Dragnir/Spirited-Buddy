#pragma once
#include "AScene.h"

class StartScene : public AScene
{
private:
	Entity* m_mouse;

public:
	void Enter() override;
	void Update(float _dt) override;
	void Exit() override;
};

