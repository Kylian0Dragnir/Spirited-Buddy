#pragma once
#include "AScene.h"

class Entity;

class LevelScene : public AScene
{
	Entity* m_wall1;
	Entity* m_wall2;
	Entity* m_ball;
	Entity* m_player;
	Entity* m_player2;
	Entity* m_ai;
	Entity* m_scoreManager;
	Entity* m_rightGoal;
	Entity* m_leftGoal;
	Entity* m_backGround;

	bool m_multiplayer;

public:
	LevelScene();

	void SetMultiplayer(bool _multi);

	void Enter() override;
	void Exit() override;
};

