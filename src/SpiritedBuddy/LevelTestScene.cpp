#include "LevelTestScene.h"
#include "AllComponent.h"
#include "ButtonLogic.h"
#include "Entity.h"
#include "TilemapLoader.h"

void LevelTestScene::OnEnter()
{
	//PORTAL
	{
		CreatePortal({ 80, 885 }, "START");
	}

	//COLLECTIBLES
	{
		CreateCollectible({ 960,300 });
	}

	//PLAYER
	{
		CreatePlayer({ 100, 920 });
	}

	//SPIRIT
	{
		CreateSpirit({ -100,-100 });
	}

	//CRATE
	{
		CreateCrate({ 1800, 920 });
	}

	//DUMMY WALL
	{
		CreateDummyWall({ 400, 840 }, "Right");
	}

	//PLAYER BARRIER
	{
		CreatePlayerBarrier({ 1200, 0 }, { 1200, 925 }, {});
	}

	//SPIRIT BARRIER
	{
		CreateSpiritBarrier({ 800, 0 }, { 800, 925 });
		CreateSpiritBarrier({ 960, 266 }, { 960, 330 }, "BARRIER");
	}

	//BUTTON
	{
		ButtonLogic* bl = CreateButton({ 1550, 930 }, ButtonMode::Hold);

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

	TilemapLoader::Load("../../Assets/test3.tmx", this, "../../Assets/Dungeon_Tileset.png", { 2.f, 2.f });
}

void LevelTestScene::OnUpdate(float _dt)
{
}

void LevelTestScene::OnExit()
{
}