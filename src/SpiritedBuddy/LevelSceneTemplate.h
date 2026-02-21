#pragma once
#include "AScene.h"
#include "Lib2D/Vector2f.h"

class Entity;
enum class ButtonMode;
class ButtonLogic;

class LevelSceneTemplate : public AScene
{
protected:
	Entity* m_player;
	Entity* m_spirit;

	std::vector<Entity*> m_playerBarriers;
	std::vector<Entity*> m_spiritBarriers;
	std::vector<Entity*> m_portals;
	std::vector<Entity*> m_collectibles;

public:
	LevelSceneTemplate();

	void Enter() override;
	void Update(float _dt) override;
	void Exit() override;

	virtual void OnEnter() {};
	virtual void OnUpdate(float _dt) {};
	virtual void OnExit() {};

	void CreateCollectible(Vector2f _pos);
	void CreatePlayer(Vector2f _pos);
	void CreateSpirit(Vector2f _pos);
	void CreatePortal(Vector2f _pos, const std::string & newSceneID);
	void CreateCrate(Vector2f _pos);
	ButtonLogic* CreateButton(Vector2f _pos, ButtonMode _mode);
	void CreateDummyWall(Vector2f _pos, const std::string& _direction);
	void CreatePlayerBarrier(Vector2f _start, Vector2f _end, const std::string & _tag = {});
	void CreateSpiritBarrier(Vector2f _start, Vector2f _end, const std::string& _tag = {});
	void CleanDestroyedEntities();
	void CleanVectors();
};

