#include "LevelTestScene.h"
#include "AllComponent.h"
#include "ButtonLogic.h"
#include "Entity.h"
#include "TilemapLoader.h"

void LevelTestScene::OnEnter()
{
	m_loader->Load("../../Assets/test4.tmx", this, "../../Assets/Dungeon_Tileset.png", { 2.f, 2.f });
}

void LevelTestScene::OnUpdate(float _dt)
{
}

void LevelTestScene::OnExit()
{
}