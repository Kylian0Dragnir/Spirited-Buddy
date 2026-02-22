#include "Level2Scene.h"
#include "AllComponent.h"
#include "ButtonLogic.h"
#include "Entity.h"
#include "TilemapLoader.h"

void Level2Scene::OnEnter()
{
	//PORTAL
	{
		CreatePortal({ 120, 500 }, "Level2Scene");
	}

	//COLLECTIBLES
	{
		CreateCollectible({ 120,690 });
	}

	//PLAYER
	{
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
		CreatePlayerBarrier({ 1472, 780 }, { 1632, 780 }, "BARRIER_TO_SWIPE");
	}

	//SPIRIT BARRIER
	{
		CreateSpiritBarrier({ 200, 600 }, { 200, 750 });
	}

	//BUTTON
	{

		//Destroy Barrier Button 
		{
			ButtonLogic* bl = CreateButton({ 1550, 930 }, ButtonMode::Hold);

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

			ButtonLogic* bl2 = CreateButton({ 1790, 930 }, ButtonMode::Hold);

			bl2->SetOnActivate([this]()
				{
					Entity* targetBarrier = FindByTag("BARRIER_TO_SWIPE");

					if (targetBarrier == nullptr)
						return;

					DestroyEntity(targetBarrier);
					CreateSpiritBarrier({ 1472, 780 }, { 1632, 780 }, "BARRIER_TO_SWIPE");
				});

			bl2->SetOnDeactivate([this]()
				{
					Entity* targetBarrier = FindByTag("BARRIER_TO_SWIPE");

					if (targetBarrier == nullptr)
						return;

					DestroyEntity(targetBarrier);
					CreatePlayerBarrier({ 1472, 780 }, { 1632, 780 }, "BARRIER_TO_SWIPE");
				});
		}
	}

	TilemapLoader::Load("../../Assets/level2.tmx", this, "../../Assets/Dungeon_Tileset.png", { 2.f, 2.f });

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