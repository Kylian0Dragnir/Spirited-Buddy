#include "Level3Scene.h"
#include "AllComponent.h"
#include "ButtonLogic.h"
#include "Entity.h"
#include "TilemapLoader.h"

void Level3Scene::OnEnter()
{
	//PORTAL
	{
		CreatePortal({ 160, 208 }, "Level3Scene");
	}

	//COLLECTIBLES
	{
		CreateCollectible({ 500,120 });
	}

	//PLAYER
	{
		CreatePlayer({ 300, 984 });
	}

	//SPIRIT
	{
		CreateSpirit({ -100,-100 });
	}

	//CRATE
	{
		CreateCrate({ 900, 984 });
	}

	//PLAYER BARRIER
	{
		CreatePlayerBarrier({ 608, 64 }, { 608, 994 }, "LEFT_BARRIER");
		CreatePlayerBarrier({ 1344, 64 }, { 1344, 994 }, "RIGHT_BARRIER"); 

		Entity* targetBarrier = FindByTag("RIGHT_BARRIER");
		targetBarrier->GetComponent<SpriteRenderer>()->SetVisible(false);
		targetBarrier->GetComponent<BoxCollider>()->SetActive(false);
	}

	//SPIRIT BARRIER
	{
		CreateSpiritBarrier({ 256, 368 }, { 1696, 368 });
	}

	//BUTTON
	{

		//Destroy Barrier Button 
		{
			ButtonLogic* bl = CreateButton({ 992, 988 }, ButtonMode::Hold);

			bl->SetOnActivate([this]()
				{
					Entity* targetLeftBarrier = FindByTag("LEFT_BARRIER");

					if (targetLeftBarrier == nullptr)
						return;

					targetLeftBarrier->GetComponent<SpriteRenderer>()->SetVisible(false);
					targetLeftBarrier->GetComponent<BoxCollider>()->SetActive(false);


					Entity* targetRightBarrier = FindByTag("RIGHT_BARRIER");

					if (targetRightBarrier == nullptr)
						return;

					targetRightBarrier->GetComponent<SpriteRenderer>()->SetVisible(true);
					targetRightBarrier->GetComponent<BoxCollider>()->SetActive(true);


				});

			bl->SetOnDeactivate([this]()
				{
					Entity* targetLeftBarrier = FindByTag("LEFT_BARRIER");

					if (targetLeftBarrier == nullptr)
						return;

					targetLeftBarrier->GetComponent<SpriteRenderer>()->SetVisible(true);
					targetLeftBarrier->GetComponent<BoxCollider>()->SetActive(true);


					Entity* targetRightBarrier = FindByTag("RIGHT_BARRIER");

					if (targetRightBarrier == nullptr)
						return;

					targetRightBarrier->GetComponent<SpriteRenderer>()->SetVisible(false);
					targetRightBarrier->GetComponent<BoxCollider>()->SetActive(false);
				});
		}
	}

	TilemapLoader::Load("../../Assets/level3.tmx", this, "../../Assets/Dungeon_Tileset.png", { 2.f, 2.f });
}

void Level3Scene::OnUpdate(float _dt)
{
}

void Level3Scene::OnExit()
{
}