#pragma once
#include <vector>
#include <string>
#include "Lib2D/Drawable.h"
#include "Updatable.h"

class Entity;

class AScene : public Drawable, public Updatable
{
private:

	std::vector<Entity*> m_entities;
	std::vector<Entity*> m_toDestroy;

public:

	AScene();
	~AScene();

	Entity* CreateEntity();
	void DestroyEntity(Entity* _ent);
	void DestroyAllEntitiesWithTag(const std::string& _tag);
	void DestroyEntityNow(Entity* _ent);
	void DestroyAllEntities();

	Entity* CreateButton(float _width, float _height);

	std::vector<Entity*> GetEntities() { return m_entities; }
	std::vector<Entity*> GetToDestroyEntities() { return m_toDestroy; }

	Entity* FindByTag(const std::string& _tag);
	std::vector<Entity*> FindAllEntitiesWithTag(const std::string& _tag);

	virtual void Enter() = 0;
	void Update(float _dt) override;
	virtual void Draw(Window* _window) override;
	virtual void Exit() = 0;
};

