#include "Level1Scene.h"
#include "AllComponent.h"
#include "ButtonLogic.h"
#include "Entity.h"
#include "TilemapLoader.h"

void Level1Scene::OnEnter()
{
	m_loader->Load("../../levels/level1.tmx", this, "../../Assets/Dungeon_Tileset.png", { 2.f, 2.f });

	ButtonLogic* bl = FindByTag("b1")->GetComponent<ButtonLogic>();

	bl->SetOnActivate([this]()
		{
			Entity* targetBarrier = FindByTag("BARRIER");

			if (targetBarrier == nullptr)
				return;

			targetBarrier->GetComponent<SpriteRenderer>()->SetVisible(false);
			targetBarrier->GetComponent<BoxCollider>()->SetActive(false);
		});

	bl->SetOnDeactivate([this]()
		{
			Entity* targetBarrier = FindByTag("BARRIER");

			if (targetBarrier == nullptr)
				return;

			targetBarrier->GetComponent<SpriteRenderer>()->SetVisible(true);
			targetBarrier->GetComponent<BoxCollider>()->SetActive(true);
		});
}

void Level1Scene::OnUpdate(float _dt)
{
}

void Level1Scene::OnExit()
{
}