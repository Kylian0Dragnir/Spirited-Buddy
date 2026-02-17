#include "MainScene.h"
#include "AllComponent.h"
#include "Entity.h"
#include "PlayerMovement.h"
#include "SpiritMovement.h"
#include "CollectibleLogic.h"
#include "Collider.h"
#include "Lib2D/InputManager.h"
#include "TilemapLoader.h"

MainScene::MainScene()
{
	m_spiritMode = false;

	m_player = CreateEntity();
	m_player->AddComponent<SpriteRenderer>()->Load("../../Assets/maelle.png");
	m_player->AddComponent<BoxCollider>(33.75f, 50.f, PLAYER_LAYER, PLAYER_LAYER | ENV_LAYER)->SetVisible(true);
	m_player->AddComponent<TagComponent>("Player");
	BoxCollider* bc = m_player->AddComponent<BoxCollider>(33.75f / 2, 1, PLAYER_LAYER, PLAYER_LAYER | ENV_LAYER);
	bc->SetVisible(true);
	bc->SetOffset(0, 25);
	m_player->AddComponent<PlayerMovement>(Key::KEY_q, Key::KEY_d, Key::KEY_SPACE);
	m_player->GetComponent<TransformComponent>()->SetScale(0.25f);
	Rigidbody2D* rb = m_player->AddComponent<Rigidbody2D>(1.f, true, 0.f);
	rb->AddImpulse({ 0,1000 });
	rb->SetGravity({ 0.f,1000.f });

	m_spirit = CreateEntity();
	m_spirit->AddComponent<BoxCollider>(33.75f, 25.f, SPIRIT_LAYER, SPIRIT_LAYER | ENV_LAYER)->SetVisible(true);
	m_spirit->AddComponent<SpiritMovement>(Key::KEY_c);
	Rigidbody2D* rb2 = m_spirit->AddComponent<Rigidbody2D>(1.0f, false, 0.f);
	m_spirit->AddComponent<TagComponent>("Spirit");

	m_playerBarrier = CreateEntity();
	SpriteRenderer* sr = m_playerBarrier->AddComponent<SpriteRenderer>();
	sr->Load("../../Assets/tempPlayerBarrier.png");
	sr->SetOpacity(96);
	m_playerBarrier->AddComponent<BoxCollider>(75, 1080, PLAYER_LAYER, PLAYER_LAYER);
	m_playerBarrier->GetComponent<TransformComponent>()->SetPos({ 1200, 540 });

	m_spiritBarrier = CreateEntity();
	sr = m_spiritBarrier->AddComponent<SpriteRenderer>();
	sr->Load("../../Assets/tempSpiritBarrier.png");
	sr->SetOpacity(96);
	m_spiritBarrier->AddComponent<BoxCollider>(75, 1080, SPIRIT_LAYER, SPIRIT_LAYER);
	m_spiritBarrier->GetComponent<TransformComponent>()->SetPos({ 800, 540 });

	CreateCollectible({ 960,300 });


	TilemapLoader::Load("../../Assets/test.tmx", this, "../../Assets/Dungeon_Tileset.png");
}

bool MainScene::GetMode()
{
	return m_spiritMode;
}

void MainScene::SwitchMode()
{
	m_spiritMode = !m_spiritMode;
}

void MainScene::Enter()
{
	m_player->GetComponent<TransformComponent>()->SetPos({ 100,100 });

	m_spirit->GetComponent<TransformComponent>()->SetPos({ -100,-100 });
}

void MainScene::Update(float _dt)
{
	AScene::Update(_dt);

	if (m_spiritMode)
	{
		m_spiritBarrier->GetComponent<SpriteRenderer>()->SetVisible(true);
		m_playerBarrier->GetComponent<SpriteRenderer>()->SetVisible(false);
	}
	else
	{
		m_spiritBarrier->GetComponent<SpriteRenderer>()->SetVisible(false);
		m_playerBarrier->GetComponent<SpriteRenderer>()->SetVisible(true);
	}
}

void MainScene::Exit()
{
}

void MainScene::DestroyCollectible(Entity* collectible)
{
	for (auto coll = m_collectibles.begin(); coll != m_collectibles.end(); ++coll)
	{
		if (*coll == collectible)
		{
			collectible->GetComponent<TransformComponent>()->SetPos({ -100,-100 });
			m_collectibles.erase(coll);
			DestroyEntity(collectible);
			return;
		}
	}
}


void MainScene::CreateCollectible(Vector2f _pos)
{
	Entity* m_coin = CreateEntity();
	m_coin->AddComponent<BoxCollider>(50, 50, ENV_LAYER, SPIRIT_LAYER | PLAYER_LAYER)->SetVisible(true);
	m_coin->AddComponent<CollectibleLogic>();
	m_coin->GetComponent<TransformComponent>()->SetPos(_pos);
	m_collectibles.push_back(m_coin);
}