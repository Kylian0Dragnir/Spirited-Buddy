#include "Level2Scene.h"
#include "AllComponent.h"
#include "ButtonLogic.h"
#include "Entity.h"
#include "TilemapLoader.h"

void Level2Scene::OnEnter()
{
	//BUTTON
	{

		//Destroy Barrier Button 
		{
			ButtonLogic* bl = CreateButton({ 1550, 905 }, ButtonMode::Hold);

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
		}

		// Swipe Barrier Mode Button
		{

			ButtonLogic* bl2 = CreateButton({ 1790, 905 }, ButtonMode::Hold);

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
	}

	//PORTAL
	{
		CreatePortal({ 120, 500 }, "Level3Scene");
	}

	//COLLECTIBLES
	{
		CreateCollectible({ 120,690 });
	}

	//PLAYER
	{
		CreateDummyPortal({ 120, 880 });
		CreatePlayer({ 120, 920 });
	}

	//SPIRIT
	{
		CreateSpirit({ -100,-100 });
	}

	//CRATE
	{
		CreateCrate({ 1700, 750 });
	}

	//PLAYER BARRIER
	{
		CreatePlayerBarrier({ 200, 830 }, { 200, 926 }, "BARRIER_TO_DESTROY");
		CreatePlayerBarrier({ 1472, 780 }, { 1632, 780 }, "PLAYERBARRIER_TO_SWIPE");
	}

	//SPIRIT BARRIER
	{
		CreateSpiritBarrier({ 200, 600 }, { 200, 750 });
		CreateSpiritBarrier({ 1472, 780 }, { 1632, 780 }, "SPIRITBARRIER_TO_SWIPE");
	}

	m_loader->Load("../../Assets/level2.tmx", this, "../../Assets/Dungeon_Tileset.png", { 2.f, 2.f });

	//Dummy Wall
	{
		CreateDummyWall({ -16, 880 }, "Left");
		CreateDummyWall({ 1936, 880 }, "Right");
	}
}

void Level2Scene::OnUpdate(float _dt)
{
}

void Level2Scene::OnExit()
{
}