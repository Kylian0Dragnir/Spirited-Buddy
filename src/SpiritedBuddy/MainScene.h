#pragma once
#include "AScene.h"

class Entity;

class MainScene : public AScene
{
	Entity* m_player;
	Entity* m_spirit;

	bool m_spiritMode;

public:
	MainScene();

	bool GetMode();
	void SwitchMode();
	void Enter() override;
	void Exit() override;
};

