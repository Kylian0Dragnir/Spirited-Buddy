#include "Level1Scene.h"
#include "AllComponent.h"
#include "ButtonLogic.h"
#include "Entity.h"
#include "TilemapLoader.h"

void Level1Scene::OnEnter()
{
	//BUTTON
	{
		ButtonLogic* bl = CreateButton({ 1450, 905 }, ButtonMode::Hold);

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
	//PORTAL
	{
		CreatePortal({ 80, 725 }, "Level2Scene");
	}

	//COLLECTIBLES
	{
		CreateCollectible({ 960,300 });
	}

	//PLAYER
	{
		CreatePlayer({ 100, 760 });
	}

	//SPIRIT
	{
		CreateSpirit({ -100,-100 });
	}

	//CRATE
	{
		CreateCrate({ 1800, 760 });
	}

	//PLAYER BARRIER
	{
		CreatePlayerBarrier({ 840, 0 }, { 840, 925 });
	}

	//SPIRIT BARRIER
	{
		CreateSpiritBarrier({ 64, 400 }, { 1856, 400 }, "BARRIER");
	}

	TilemapLoader::Load("./Assets/level1.tmx", this, "./Assets/Dungeon_Tileset.png", { 2.f, 2.f });
}

void Level1Scene::OnUpdate(float _dt)
{
}

void Level1Scene::OnExit()
{
}