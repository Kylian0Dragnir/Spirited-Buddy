#include "Level1Scene.h"
#include "AllComponent.h"
#include "ButtonLogic.h"
#include "Entity.h"
#include "TilemapLoader.h"

void Level1Scene::OnEnter()
{
	//PORTAL
	{
		CreatePortal({ 80, 725 }, "Level1Scene");
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

	//BUTTON
	{
		ButtonLogic* bl = CreateButton({ 1450, 930 }, ButtonMode::Hold);

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

	TilemapLoader::Load("../../Assets/level1.tmx", this, "../../Assets/Dungeon_Tileset.png", { 2.f, 2.f });
}

void Level1Scene::OnUpdate(float _dt)
{
}

void Level1Scene::OnExit()
{
}