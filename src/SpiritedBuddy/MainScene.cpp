#include "MainScene.h"
#include "AllComponent.h"
#include "Entity.h"
#include "PlayerMovement.h"
#include "SpiritMovement.h"
#include "PhysicObjectMovement.h" 
#include "CollectibleLogic.h"
#include "PortalLogic.h"
#include "Collider.h"
#include "Lib2D/InputManager.h"
#include "TilemapLoader.h"

MainScene::MainScene()
{

}

bool& MainScene::GetMode()
{
	return m_spiritMode;
}

void MainScene::SwitchMode()
{
	m_spiritMode = !m_spiritMode;
	m_player->GetComponent<Rigidbody2D>()->SetVelocity({ 0, 0 });
	m_spirit->GetComponent<Rigidbody2D>()->SetVelocity({ 0, 0 });
}

void MainScene::Enter()
{
	m_spiritMode = false;

	//PORTAL
	{
		CreatePortal({ 80, 750 }, "START");
	}

	//COLLECTIBLES
	{
		CreateCollectible({ 960,300 });
		CreateCollectible({ 960,400 });
	}

	//PLAYER
	{
		CreatePlayer({ 100,100 });
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

		crate->AddComponent<PhysicObjectMovement>(Key::KEY_k, Key::KEY_m);
		m_player->GetComponent<TransformComponent>()->SetScale(0.25f);

		Rigidbody2D* rb = crate->AddComponent<Rigidbody2D>(1.f, true, 0.f);
		rb->AddImpulse({ 0,1000 });
		rb->SetGravity({ 0.f,1000.f });
	}

	//PLAYER BARRIER
	{
		CreatePlayerBarrier({ 1200, 540 });
	}

	//SPIRIT BARRIER
	{
		CreateSpiritBarrier({ 800, 540 });
		CreateSpiritBarrier({ 960, 540 }, "BARRIER");
	}

	TilemapLoader::Load("../../Assets/test.tmx", this, "../../Assets/Dungeon_Tileset.png");

}

void MainScene::Update(float _dt)
{
	AScene::Update(_dt);

	CleanDestroyedEntities();

	if (m_spiritMode)
	{
		for (Entity* sb : m_spiritBarriers)
		{
			sb->GetComponent<SpriteRenderer>()->SetVisible(true);
			sb->GetComponent<BoxCollider>()->SetActive(true);
		}
		for (Entity* pb : m_playerBarriers)
		{
			pb->GetComponent<SpriteRenderer>()->SetVisible(false);
			pb->GetComponent<BoxCollider>()->SetActive(false);
		}
	}
	else
	{
		for (Entity* sb : m_spiritBarriers)
		{
			sb->GetComponent<SpriteRenderer>()->SetVisible(false);
			sb->GetComponent<BoxCollider>()->SetActive(false);
		}
		for (Entity* pb : m_playerBarriers)
		{
			pb->GetComponent<SpriteRenderer>()->SetVisible(true);
			pb->GetComponent<BoxCollider>()->SetActive(true);
		}
	}

	if (m_collectibles.empty())
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
	m_coin->AddComponent<BoxCollider>(50, 50, ENV_LAYER, SPIRIT_LAYER | PLAYER_LAYER)->SetVisible(true);
	m_coin->AddComponent<CollectibleLogic>();
	m_coin->GetComponent<TransformComponent>()->SetPos(_pos);
	m_collectibles.push_back(m_coin);
}

void MainScene::CreatePlayer(Vector2f _pos)
{
	m_player = CreateEntity();
	m_player->AddComponent<SpriteRenderer>()->Load("../../Assets/maelle.png");
	m_player->AddComponent<TagComponent>("Player");

	//Solid Collider
	m_player->AddComponent<BoxCollider>(33.75f, 50.f, PLAYER_LAYER, PLAYER_LAYER | ENV_LAYER | SPIRIT_LAYER)->SetVisible(true);

	//Grounded Trigger Collider
	BoxCollider* bc = m_player->AddComponent<BoxCollider>(33.75f / 2, 1, PLAYER_LAYER, PLAYER_LAYER | ENV_LAYER);
	bc->SetVisible(true);
	bc->SetTrigger(true);
	bc->SetOffset(0, 25);

	m_player->AddComponent<PlayerMovement>(Key::KEY_q, Key::KEY_d, Key::KEY_SPACE);

	m_player->GetComponent<TransformComponent>()->SetPos(_pos);
	m_player->GetComponent<TransformComponent>()->SetScale(0.25f);

	m_player->AddComponent<Rigidbody2D>(1.f, true, 0.f)->SetGravity({ 0.f,1000.f });

}

void MainScene::CreateSpirit(Vector2f _pos)
{
	m_spirit = CreateEntity();
	m_spirit->AddComponent<TagComponent>("Spirit");

	//Solid Collider
	m_spirit->AddComponent<BoxCollider>(33.75f, 25.f, SPIRIT_LAYER, SPIRIT_LAYER | ENV_LAYER)->SetVisible(true);

	//Interaction Trigger Collider
	CircleCollider* cc = m_spirit->AddComponent<CircleCollider>(40.f, SPIRIT_LAYER, SPIRIT_LAYER | PLAYER_LAYER);
	cc->SetVisible(true);
	cc->SetTrigger(true);

	m_spirit->AddComponent<SpiritMovement>(Key::KEY_c);

	m_spirit->GetComponent<TransformComponent>()->SetPos(_pos);

	m_spirit->AddComponent<Rigidbody2D>(1.0f, false, 0.f);
}

void MainScene::CreatePortal(Vector2f _pos, const std::string& newSceneID)
{
	Entity* portal = CreateEntity();

	SpriteRenderer* sr = portal->AddComponent<SpriteRenderer>();
	sr->Load("../../Assets/Portal-Sheet.png");
	sr->SetVisible(false);

	CircleCollider* cc = portal->AddComponent<CircleCollider>(48, ENV_LAYER, PLAYER_LAYER);
	cc->SetActive(false);
	cc->SetVisible(true);
	cc->SetTrigger(true);

	portal->AddComponent<PortalLogic>(newSceneID);

	TransformComponent* transform = portal->GetComponent<TransformComponent>();
	transform->SetPos(_pos);
	transform->SetScale(1.5f);

	m_portals.push_back(portal);
}

void MainScene::CreatePlayerBarrier(Vector2f _pos, const std::string& _tag)
{
	Entity* playerBarrier = CreateEntity();

	SpriteRenderer* sr = playerBarrier->AddComponent<SpriteRenderer>();
	TagComponent* tc = playerBarrier->AddComponent<TagComponent>("PLAYER_BARRIER");
	if (!_tag.empty())
		tc->AddTag(_tag);
	sr->Load("../../Assets/tempPlayerBarrier.png");
	sr->SetOpacity(96);

	playerBarrier->AddComponent<BoxCollider>(75, 1080, PLAYER_LAYER, PLAYER_LAYER);
	playerBarrier->GetComponent<TransformComponent>()->SetPos(_pos);

	m_playerBarriers.push_back(playerBarrier);
}

void MainScene::CreateSpiritBarrier(Vector2f _pos, const std::string& _tag)
{
	Entity* spiritBarrier = CreateEntity();

	SpriteRenderer* sr = spiritBarrier->AddComponent<SpriteRenderer>();
	TagComponent* tc = spiritBarrier->AddComponent<TagComponent>("SPIRIT_BARRIER");
	if (!_tag.empty())
		tc->AddTag(_tag);
	sr->Load("../../Assets/tempSpiritBarrier.png");
	sr->SetOpacity(96);

	spiritBarrier->AddComponent<BoxCollider>(75, 1080, SPIRIT_LAYER, SPIRIT_LAYER);
	spiritBarrier->GetComponent<TransformComponent>()->SetPos(_pos);

	m_spiritBarriers.push_back(spiritBarrier);
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