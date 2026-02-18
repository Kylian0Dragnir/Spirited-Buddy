#pragma once
#include "AScene.h"
#include "Lib2D/Vector2f.h"

class Entity;

class MainScene : public AScene
{
	Entity* m_player;
	Entity* m_spirit;

	Entity* m_playerBarrier;
	Entity* m_spiritBarrier;
	Entity* m_spiritBarrier2;

	Entity* m_portal;

	std::vector<Entity*> m_collectibles;

	bool m_spiritMode;

public:
	MainScene();

	bool& GetMode();
	void SwitchMode();
	void Enter() override;
	void Update(float _dt) override;
	void Exit() override;

	void DestroyCollectible(Entity* collectible);
	void CreateCollectible(Vector2f _pos);
};

