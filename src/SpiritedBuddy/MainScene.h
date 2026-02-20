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

	std::vector<Entity*> m_portals;

	std::vector<Entity*> m_collectibles;


	Entity* m_wall1;
	Entity* m_wall2;

public:
	MainScene();

	void Enter() override;
	void Update(float _dt) override;
	void Exit() override;

	void CreateCollectible(Vector2f _pos);
	void CreatePlayer(Vector2f _pos);
	void CreateSpirit(Vector2f _pos);
	void CreatePortal(Vector2f _pos, const std::string & newSceneID);
	void CreatePlayerBarrier(Vector2f _pos, const std::string& _tag = {});
	void CreateSpiritBarrier(Vector2f _pos, const std::string& _tag = {});
	void CreateWall(Vector2f _pos, Vector2f _size, const std::string& _tag = {});
	void CleanDestroyedEntities();
	void CleanVectors();
};

