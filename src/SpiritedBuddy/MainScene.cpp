#include "MainScene.h"
#include "AllComponent.h"
#include "Entity.h"
#include "PlayerMovement.h"
#include "SpiritLogic.h"
#include "PhysicObjectMovement.h" 
#include "CollectibleLogic.h"
#include "PossessionLogic.h"
#include "PortalLogic.h"
#include "ButtonLogic.h"
#include "Collider.h"
#include "Lib2D/InputManager.h"
#include "TilemapLoader.h"

#include <iostream>

MainScene::MainScene()
{

}

void MainScene::Enter()
{
	//PORTAL
	{
		CreatePortal({ 80, 750 }, "START");
	}

	//COLLECTIBLES
	{
		CreateCollectible({ 960,300 });
	}

	//PLAYER
	{
		CreatePlayer({ 100, 750 });
	}

	//SPIRIT
	{
		CreateSpirit({ -100,-100 });
	}

	//CRATE
	{
		Entity* crate = CreateEntity();

		//Solid Collider
		crate->AddComponent<BoxCollider>(40.f, 40.f, PLAYER_LAYER, PLAYER_LAYER | ENV_LAYER | SPIRIT_LAYER)->SetVisible(true);

		crate->AddComponent<TagComponent>("CRATE")->AddTag("PhysicObject");

		crate->AddComponent<PossessionLogic>();
		crate->AddComponent<PhysicObjectMovement>(Key::KEY_q, Key::KEY_d);

		crate->GetComponent<TransformComponent>()->SetPos({ 1800, 750 });

		crate->AddComponent<Rigidbody2D>(1.f, true, 0.f)->SetGravity({ 0.f,1000.f });
	}

	//PLAYER BARRIER
	{
		CreatePlayerBarrier({ 1200, 0 }, { 1200, 960 }, {});
	}

	//SPIRIT BARRIER
	{
		CreateSpiritBarrier({ 800, 0 }, { 800, 960 });
		CreateSpiritBarrier({ 960, 266 }, { 960, 330 }, "BARRIER");
	}

	//BUTTON
	{
		Entity* button = CreateEntity();

		//Solid Collider
		BoxCollider* solidCollider = button->AddComponent<BoxCollider>(50.f, 20.f, PLAYER_LAYER, PLAYER_LAYER);
		solidCollider->SetVisible(true);
		solidCollider->SetOffset(0, 10);

		//Trigger Collider
		BoxCollider* triggerCollider = button->AddComponent<BoxCollider>(35, 15.f, PLAYER_LAYER, PLAYER_LAYER);
		triggerCollider->SetVisible(true);
		triggerCollider->SetTrigger(true);
		triggerCollider->SetOffset(0, -7.5f);

		button->AddComponent<TagComponent>("BUTTON")->AddTag("PhysicObject");

		ButtonLogic* b = button->AddComponent<ButtonLogic>(ButtonMode::Hold);

		b->SetOnActivate([this]()
			{
				Entity* targetBarrier = FindByTag("BARRIER");
				targetBarrier->GetComponent<SpriteRenderer>()->SetVisible(false);
				targetBarrier->GetComponent<BoxCollider>()->SetActive(false);
			});

		b->SetOnDeactivate([this]()
			{
				Entity* targetBarrier = FindByTag("BARRIER");
				targetBarrier->GetComponent<SpriteRenderer>()->SetVisible(true);
				targetBarrier->GetComponent<BoxCollider>()->SetActive(true);
			});


		button->GetComponent<TransformComponent>()->SetPos({ 1550, 940 });
	}

	TilemapLoader::Load("../../Assets/test.tmx", this, "../../Assets/Dungeon_Tileset.png");
}

void MainScene::Update(float _dt)
{
	AScene::Update(_dt);

	CleanDestroyedEntities();

	//if (m_spirit->GetComponent<SpiritLogic>()->IsPossessing())
	//{
	//	for (Entity* sb : m_spiritBarriers)
	//	{
	//		sb->GetComponent<SpriteRenderer>()->SetVisible(false);
	//		sb->GetComponent<BoxCollider>()->SetActive(false);
	//	}
	//	for (Entity* pb : m_playerBarriers)
	//	{
	//		pb->GetComponent<SpriteRenderer>()->SetVisible(true);
	//		pb->GetComponent<BoxCollider>()->SetActive(true);
	//	}
	//}
	//else
	//{
	//	for (Entity* sb : m_spiritBarriers)
	//	{
	//		sb->GetComponent<SpriteRenderer>()->SetVisible(true);
	//		sb->GetComponent<BoxCollider>()->SetActive(true);
	//	}
	//	for (Entity* pb : m_playerBarriers)
	//	{
	//		pb->GetComponent<SpriteRenderer>()->SetVisible(false);
	//		pb->GetComponent<BoxCollider>()->SetActive(false);
	//	}
	// }

	if (m_collectibles.empty() || InputManager::Get().IsKeyDown(Key::KEY_p))
	{
		for (Entity* p : m_portals)
		{
			p->GetComponent<PortalLogic>()->Appear();
		}
	}

	if (InputManager::Get().IsKeyDown(Key::KEY_BACKSPACE))
	{
		DestroyAllEntitiesWithTag("BARRIER");
	}
}

void MainScene::Exit()
{
	DestroyAllEntities();
	CleanVectors();
}

void MainScene::CreateCollectible(Vector2f _pos)
{
	Entity* m_coin = CreateEntity();
	m_coin->AddComponent<BoxCollider>(25.f, 25.f, ENV_LAYER, SPIRIT_LAYER | PLAYER_LAYER)->SetVisible(true);
	m_coin->AddComponent<TagComponent>("COLLECTIBLE");
	m_coin->AddComponent<CollectibleLogic>();
	m_coin->GetComponent<TransformComponent>()->SetPos(_pos);
	m_collectibles.push_back(m_coin);
}

void MainScene::CreatePlayer(Vector2f _pos)
{
	m_player = CreateEntity();
	SpriteRenderer* sr = m_player->AddComponent<SpriteRenderer>();
	sr->Load("../../Assets/Player/player_sheet.png");
	sr->SetFrame(32, 32, 128, 0);
	m_player->AddComponent<TagComponent>("Player");

	//Solid Collider
	m_player->AddComponent<BoxCollider>(33.75f, 50.f, PLAYER_LAYER, PLAYER_LAYER | ENV_LAYER | SPIRIT_LAYER)->SetVisible(true);

	//Grounded Trigger Collider
	BoxCollider* bc = m_player->AddComponent<BoxCollider>(33.75f / 2, 1, PLAYER_LAYER, PLAYER_LAYER | ENV_LAYER);
	bc->SetVisible(true);
	bc->SetTrigger(true);
	bc->SetOffset(0, 25);

	m_player->AddComponent<PossessionLogic>()->SetPossessed(true);
	m_player->AddComponent<PlayerMovement>(Key::KEY_q, Key::KEY_d, Key::KEY_SPACE)->SetAnimation(PlayerAnimState::Respawn);

	m_player->GetComponent<TransformComponent>()->SetPos(_pos);
	m_player->GetComponent<TransformComponent>()->SetScale({1.5f, 1.5f});

	m_player->AddComponent<Rigidbody2D>(1.f, true, 0.f)->SetGravity({ 0.f,1000.f });
}

void MainScene::CreateSpirit(Vector2f _pos)
{
	m_spirit = CreateEntity();
	m_spirit->AddComponent<TagComponent>("Spirit");

	SpriteRenderer* sr = m_spirit->AddComponent<SpriteRenderer>();
	sr->Load("../../Assets/Spirit.png");
	sr->SetFrame(64, 64, 0, 0);
	sr->SetOffset({ 0,-15 });

	//Solid Collider
	m_spirit->AddComponent<CircleCollider>(14.f, SPIRIT_LAYER, SPIRIT_LAYER | ENV_LAYER)->SetVisible(true);

	//Interaction Trigger Collider
	CircleCollider* cc = m_spirit->AddComponent<CircleCollider>(40.f, SPIRIT_LAYER, SPIRIT_LAYER | PLAYER_LAYER);
	cc->SetVisible(true);
	cc->SetTrigger(true);

	m_spirit->AddComponent<SpiritLogic>(Key::KEY_c,m_player);

	m_spirit->GetComponent<TransformComponent>()->SetPos(_pos);

	m_spirit->AddComponent<Rigidbody2D>(1.0f, false, 0.f);
}

void MainScene::CreatePortal(Vector2f _pos, const std::string& newSceneID)
{
	Entity* portal = CreateEntity();

	portal->AddComponent<TagComponent>("PORTAL");

	SpriteRenderer* sr = portal->AddComponent<SpriteRenderer>();
	sr->Load("../../Assets/Portal-Sheet.png");
	sr->SetVisible(false);

	CircleCollider* cc = portal->AddComponent<CircleCollider>(48.f, ENV_LAYER, PLAYER_LAYER);
	cc->SetActive(false);
	cc->SetTrigger(true);

	portal->AddComponent<PortalLogic>(newSceneID);

	TransformComponent* transform = portal->GetComponent<TransformComponent>();
	transform->SetPos(_pos);
	transform->SetScale({ 1.5f, 1.5f });

	m_portals.push_back(portal);
}

void MainScene::CreatePlayerBarrier(Vector2f _start, Vector2f _end, const std::string& _tag)
{
	Entity* barrier = CreateEntity();

	float height = abs(_end.GetY() - _start.GetY());

	Vector2f center = {
		(_start.GetX() + _end.GetX()) * 0.5f,
		(_start.GetY() + _end.GetY()) * 0.5f
	};

	SpriteRenderer* sr = barrier->AddComponent<SpriteRenderer>();
	sr->Load("../../Assets/barrier/blue_barrier.png");
	sr->SetFrame(16, 16, 0, 0);
	sr->SetOpacity(255);
	sr->SetTiledSize({ 48.f, height });

	barrier->AddComponent<BoxCollider>(48.f, height, PLAYER_LAYER, PLAYER_LAYER);

	TransformComponent* transform = barrier->GetComponent<TransformComponent>();
	transform->SetPos(center);
	transform->SetScale({ 3.f, 2.f });

	TagComponent* tc = barrier->AddComponent<TagComponent>("PLAYER_BARRIER");
	if (!_tag.empty())
		tc->AddTag(_tag);

	m_playerBarriers.push_back(barrier);
}

void MainScene::CreateSpiritBarrier(Vector2f _start, Vector2f _end, const std::string& _tag)
{
	Entity* barrier = CreateEntity();

	float height = abs(_end.GetY() - _start.GetY());

	Vector2f center = {
		(_start.GetX() + _end.GetX()) * 0.5f,
		(_start.GetY() + _end.GetY()) * 0.5f
	};

	SpriteRenderer* sr = barrier->AddComponent<SpriteRenderer>();
	sr->Load("../../Assets/barrier/green_barrier.png");
	sr->SetFrame(16, 16, 0, 0);
	sr->SetOpacity(255);
	sr->SetTiledSize({ 48.f, height });

	barrier->AddComponent<BoxCollider>(48.f, height, SPIRIT_LAYER, SPIRIT_LAYER);

	TransformComponent* transform = barrier->GetComponent<TransformComponent>();
	transform->SetPos(center);
	transform->SetScale({ 3.f, 2.f });

	TagComponent* tc = barrier->AddComponent<TagComponent>("SPIRIT_BARRIER");
	if (!_tag.empty())
		tc->AddTag(_tag);

	m_spiritBarriers.push_back(barrier);
}

void MainScene::CleanDestroyedEntities()
{
	for (int i = m_collectibles.size() - 1; i >= 0; i--)
	{
		if (m_collectibles[i]->GetComponent<TransformComponent>() == nullptr)
			m_collectibles.erase(m_collectibles.begin() + i);
	}

	for (int i = m_playerBarriers.size() - 1; i >= 0; i--)
	{
		if (m_playerBarriers[i]->GetComponent<TransformComponent>() == nullptr)
			m_playerBarriers.erase(m_playerBarriers.begin() + i);
	}

	for (int i = m_spiritBarriers.size() - 1; i >= 0; i--)
	{
		if (m_spiritBarriers[i]->GetComponent<TransformComponent>() == nullptr)
			m_spiritBarriers.erase(m_spiritBarriers.begin() + i);
	}

	for (int i = m_portals.size() - 1; i >= 0; i--)
	{
		if (m_portals[i]->GetComponent<TransformComponent>() == nullptr)
			m_portals.erase(m_portals.begin() + i);
	}
}

void MainScene::CleanVectors()
{
	for (int i = m_collectibles.size() - 1; i >= 0; i--)
		m_collectibles.erase(m_collectibles.begin() + i);

	for (int i = m_playerBarriers.size() - 1; i >= 0; i--)
		m_playerBarriers.erase(m_playerBarriers.begin() + i);

	for (int i = m_spiritBarriers.size() - 1; i >= 0; i--)
		m_spiritBarriers.erase(m_spiritBarriers.begin() + i);

	for (int i = m_portals.size() - 1; i >= 0; i--)
		m_portals.erase(m_portals.begin() + i);
}