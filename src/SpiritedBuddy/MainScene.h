#pragma once
#include "AScene.h"
#include "Lib2D/Vector2f.h"

class Entity;

class MainScene : public AScene
{
	Entity* m_player;
	Entity* m_spirit;

	std::vector<Entity*> m_playerBarriers;
	std::vector<Entity*> m_spiritBarriers;
	//Entity* m_playerBarrier;
	//Entity* m_spiritBarrier;
	//Entity* m_spiritBarrier2;

	std::vector<Entity*> m_portals;

	//Entity* m_portal;

	std::vector<Entity*> m_collectibles;

public:
	MainScene();

	void Enter() override;
	void Update(float _dt) override;
	void Exit() override;

	void CreateCollectible(Vector2f _pos);
	void CreatePlayer(Vector2f _pos);
	void CreateSpirit(Vector2f _pos);
	void CreatePortal(Vector2f _pos, const std::string & newSceneID);
	void CreatePlayerBarrier(Vector2f _start, Vector2f _end, const std::string & _tag = {});
	void CreateSpiritBarrier(Vector2f _start, Vector2f _end, const std::string& _tag = {});
	void CleanDestroyedEntities();
	void CleanVectors();
};

