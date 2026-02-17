#include "MainScene.h"
#include "AllComponent.h"
#include "Entity.h"
#include "PlayerMovement.h"
#include "SpiritMovement.h"
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

	Entity* barierTest = CreateEntity();
	barierTest->AddComponent<BoxCollider>(75, 1080, PLAYER_LAYER, PLAYER_LAYER)->SetVisible(true);
	barierTest->GetComponent<TransformComponent>()->SetPos({ 960, 540 });

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

void MainScene::Exit()
{
}
