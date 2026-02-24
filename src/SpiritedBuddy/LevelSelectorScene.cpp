#include "LevelSelectorScene.h"
#include "TilemapLoader.h"
#include "Entity.h"
#include "AllComponent.h"
#include "PortalLogic.h"
#include "CakeLogic.h"
#include "TextComponent.h"
#include "SpriteRenderer.h"
#include "param.h"
#include "Lib2D/AudioEngine.h"

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
		CreateDummyPortal({ 120, 920 });
		CreatePlayer({ 120, 930 });
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

	if (m_player->GetComponent<Rigidbody2D>()->GetVelocity().Length() > 5000.f)
	{
		if (FindByTag("cake"))
			return;

		CreateCake({ 1500, 975 });
	}
}

void LevelSelectorScene::OnExit()
{
	AudioEngine::Get().StopSound("PORTAL_OPEN");
}

void LevelSelectorScene::CreateCake(Vector2f _pos)
{
	Entity* cake = CreateEntity();

	cake->AddComponent<TagComponent>("cake")->AddTag("PhysicObject");

	cake->AddComponent<SpriteRenderer>()->Load("../../Assets/cake.png");

	cake->AddComponent<CircleCollider>(25.f, PLAYER_LAYER, PLAYER_LAYER)->SetTrigger(true);
	BoxCollider* bc = cake->AddComponent<BoxCollider>(45.f, 30.f, PLAYER_LAYER, PLAYER_LAYER);
	bc->SetVisible(false);
	bc->SetOffset( 0, 10 );

	TextComponent* text = cake->AddComponent<TextComponent>("../../Assets/Bungee-Regular.otf", 15);
	text->SetText("THE CAKE IS A LIE !");
	text->SetVisible(false);
	text->SetOffset({ 0, -45 });

	TransformComponent* transform = cake->GetComponent<TransformComponent>();
	transform->SetPos(_pos);
	transform->SetScale({ 0.4f, 0.4f });

	cake->AddComponent<CakeLogic>();
}
