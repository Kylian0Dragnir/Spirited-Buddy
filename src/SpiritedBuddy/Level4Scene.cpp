#include "Level4Scene.h"
#include "AllComponent.h"
#include "ButtonLogic.h"
#include "Entity.h"
#include "TilemapLoader.h"

void Level4Scene::OnEnter()
{
	//PORTAL
	{
		CreatePortal({ 1760, 960 - 16 }, "LevelSelectorScene");
	}

	//COLLECTIBLES
	{
		CreateCollectible({ 992,160 });
		CreateCollectible({ 1736 + 16,160 });
	}

	//PLAYER
	{
		CreatePlayer({ 200, 984 });
	}

	//SPIRIT
	{
		CreateSpirit({ -100,-100 });
	}

	//PLAYER BARRIER
	{
		CreatePlayerBarrier({ 928, 992+16 }, { 1024, 992+16 });
	}

	//SPIRIT BARRIER
	{
		CreateSpiritBarrier({1696, 368}, { 1824, 368});
		CreateSpiritBarrier({ 1120, 96 }, { 1120, 224 });
	}

	TilemapLoader::Load("./Assets/level4.tmx", this, "./Assets/Dungeon_Tileset.png", { 2.f, 2.f });

	//DUMMY WALL
	{
		CreateDummyWall({ 960 + 16, 1056 + 16 }, "Down");
		CreateDummyWall({ 960 + 16 + 32, 0 + 16 }, "Up");
		CreateDummyWall({ 1280 + 16, 224 + 16 }, "Plateform");
	}
}

void Level4Scene::OnUpdate(float _dt)
{
}

void Level4Scene::OnExit()
{
}