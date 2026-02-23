#include "LevelSelectorScene.h"
#include "TilemapLoader.h"
#include "Entity.h"
#include "AllComponent.h"
#include "PortalLogic.h"
#include "param.h"

void LevelSelectorScene::OnEnter()
{
	//PORTAL
	{
		CreatePortal({ 400, 750 }, "Level1Scene")->SetActive(false);
		CreatePortal({ 500, 750 }, "Level2Scene")->SetActive(false);
		CreatePortal({ 600, 750 }, "Level3Scene")->SetActive(false);
		CreatePortal({ 700, 750 }, "Level4Scene")->SetActive(false);
	}

	//Text
	{
		CreateText({ 400, 700 }, "LEVEL 1", 20);
		CreateText({ 500, 700 }, "LEVEL 2", 20);
		CreateText({ 600, 700 }, "LEVEL 3", 20);
		CreateText({ 700, 700 }, "LEVEL 4", 20);
	}

	//PLAYER
	{
		CreatePlayer({ 120, 984 });
	}

	TilemapLoader::Load("../../Assets/levelSelector.tmx", this, "../../Assets/Dungeon_Tileset.png", { 2.f, 2.f });
}

void LevelSelectorScene::OnUpdate(float _dt)
{
	for (int i = 0; i < Param::Get().GetLevelUnlockedCount(); i++)
	{
		if (i > m_portals.size() - 1)
			return;

		m_portals[i]->GetComponent<PortalLogic>()->SetActive(true);
	}
}

void LevelSelectorScene::OnExit()
{
}
