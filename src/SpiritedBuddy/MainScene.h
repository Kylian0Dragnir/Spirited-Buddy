#pragma once
#include "AScene.h"

class Entity;

class MainScene : public AScene
{
	Entity* m_player;
	Entity* m_spirit;

	Entity* m_ground;
	Entity* m_ground2;
	Entity* m_ground3;

	Entity* m_wall;
	Entity* m_wall2;
	Entity* m_wall3;
	Entity* m_wall4;

	bool m_spiritMode;

public:
	MainScene();

	bool GetMode();
	void SwitchMode();
	void Enter() override;
	void Exit() override;
};

