#include "Level2Scene.h"
#include "AllComponent.h"
#include "ButtonLogic.h"
#include "Entity.h"
#include "TilemapLoader.h"

void Level2Scene::OnEnter()
{

	m_loader->Load("../../levels/level2.tmx", this, "../../Assets/Dungeon_Tileset.png", { 2.f, 2.f });

	Entity* spiritBarrier = FindByTag("SPIRITBARRIER_TO_SWIPE");
	spiritBarrier->GetComponent<Collider>()->SetActive(false);
	spiritBarrier->GetComponent<SpriteRenderer>()->SetVisible(false);

	ButtonLogic* bl = FindByTag("b1")->GetComponent<ButtonLogic>();

	bl->SetOnActivate([this]()
		{
			Entity* targetBarrier = FindByTag("BARRIER_TO_DESTROY");

			if (targetBarrier == nullptr)
				return;

			targetBarrier->GetComponent<SpriteRenderer>()->SetVisible(false);
			targetBarrier->GetComponent<BoxCollider>()->SetActive(false);
		});

	bl->SetOnDeactivate([this]()
		{
			Entity* targetBarrier = FindByTag("BARRIER_TO_DESTROY");

			if (targetBarrier == nullptr)
				return;

			targetBarrier->GetComponent<SpriteRenderer>()->SetVisible(true);
			targetBarrier->GetComponent<BoxCollider>()->SetActive(true);
		});

	ButtonLogic* bl2 = FindByTag("b2")->GetComponent<ButtonLogic>();

	bl2->SetOnActivate([this]()
		{
			Entity* playerBarrier = FindByTag("PLAYERBARRIER_TO_SWIPE");
			Entity* spiritBarrier = FindByTag("SPIRITBARRIER_TO_SWIPE");


			playerBarrier->GetComponent<Collider>()->SetActive(false);
			playerBarrier->GetComponent<SpriteRenderer>()->SetVisible(false);

			spiritBarrier->GetComponent<Collider>()->SetActive(true);
			spiritBarrier->GetComponent<SpriteRenderer>()->SetVisible(true);
		});

	bl2->SetOnDeactivate([this]()
		{
			Entity* playerBarrier = FindByTag("PLAYERBARRIER_TO_SWIPE");
			Entity* spiritBarrier = FindByTag("SPIRITBARRIER_TO_SWIPE");

			playerBarrier->GetComponent<Collider>()->SetActive(true);
			playerBarrier->GetComponent<SpriteRenderer>()->SetVisible(true);

			spiritBarrier->GetComponent<Collider>()->SetActive(false);
			spiritBarrier->GetComponent<SpriteRenderer>()->SetVisible(false);
		});
}

void Level2Scene::OnUpdate(float _dt)
{
}

void Level2Scene::OnExit()
{
}