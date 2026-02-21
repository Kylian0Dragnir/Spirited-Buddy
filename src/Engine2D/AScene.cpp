#include "AScene.h"
#include "Drawable.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "SpriteRenderer.h"
#include "ButtonComponent.h"
#include "BoxCollider.h"
#include "CollisionSystem.h"

AScene::AScene()
{
}

AScene::~AScene()
{
}

Entity* AScene::CreateEntity()
{
	Entity* ent = new Entity;
	m_entities.push_back(ent);
	ent->AddComponent<TransformComponent>();
	return ent;
}

void AScene::DestroyEntity(Entity* _ent)
{
	m_toDestroy.push_back(_ent);
}

void AScene::DestroyAllEntitiesWithTag(const std::string& _tag)
{
	for(Entity* ent : FindAllEntitiesWithTag(_tag))
		DestroyEntity(ent);
}

void AScene::DestroyEntityNow(Entity* _ent)
{
	auto it = std::find(m_entities.begin(), m_entities.end(), _ent);

	if (it != m_entities.end())
	{
		CollisionSystem::GetInstance().Clear(*it);
		delete *it;
		m_entities.erase(it);
	}
}

void AScene::DestroyAllEntities()
{
	for (int i = m_entities.size() - 1; i >= 0; i--)
		DestroyEntityNow(m_entities[i]);
}

Entity* AScene::CreateButton(float _width, float _height)
{
	Entity* ent = CreateEntity();
	ent->AddComponent<ButtonComponent>();
	ent->AddComponent<BoxCollider>(_width, _height, NONE, NONE);
	return ent;
}

Entity* AScene::FindByTag(const std::string& _tag)
{
	for (Entity* ent : m_entities)
	{
		if (TagComponent* tag = ent->GetComponent<TagComponent>())
		{
			if (tag->Is(_tag))
				return ent;
		}
	}

	return nullptr;
}

std::vector<Entity*> AScene::FindAllEntitiesWithTag(const std::string& _tag)
{
	std::vector<Entity*> result;

	for (Entity* ent : m_entities)
	{
		if (TagComponent* tag = ent->GetComponent<TagComponent>())
		{
			if (tag->Is(_tag))
				result.push_back(ent);
		}
	}

	return result;
}

void AScene::Update(float _dt)
{
	for (Entity* ent : m_entities)
	{
		ent->Update(_dt);
	}

	for (Entity* e : m_toDestroy)
	{
		auto it = std::find(m_entities.begin(), m_entities.end(), e);
		if (it != m_entities.end())
		{
			CollisionSystem::GetInstance().Clear(*it);
			delete* it;
			m_entities.erase(it);
		}
	}

	m_toDestroy.clear();
}

void AScene::Draw(Window* _window)
{
	for (Entity* ent : m_entities)
	{
		ent->Draw(_window);
	}
}
