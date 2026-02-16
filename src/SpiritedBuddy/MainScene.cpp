#include "MainScene.h"
#include "AllComponent.h"
#include "Entity.h"
#include "PlayerMovement.h"
#include "SpiritMovement.h"
#include "Lib2D/InputManager.h"

MainScene::MainScene()
{
	m_spiritMode = false;

	m_player = CreateEntity();
	m_player->AddComponent<SpriteRenderer>()->Load("../../Assets/maelle.png");
	m_player->AddComponent<BoxCollider>(33.75f, 50.f)->SetVisible(true);
	m_player->AddComponent<TagComponent>("Player");
	BoxCollider* bc = m_player->AddComponent<BoxCollider>(33.75f/2,1);
	bc->SetVisible(true);
	bc->SetOffset(0, 25);
	m_player->AddComponent<PlayerMovement>(Key::KEY_q, Key::KEY_d, Key::KEY_SPACE);
	m_player->GetComponent<TransformComponent>()->SetScale(0.25f);
	Rigidbody2D* rb = m_player->AddComponent<Rigidbody2D>();
	rb->SetRestitution(0);
	rb->AddImpulse({ 0,1000 });
	rb->SetGravity({ 0.f,1000.f });


	m_spirit = CreateEntity();
	m_spirit->AddComponent<BoxCollider>(33.75f, 25.f)->SetVisible(true);
	m_spirit->AddComponent<SpiritMovement>(Key::KEY_c);


	m_ground = CreateEntity();
	m_ground->AddComponent<BoxCollider>(1920, 50)->SetVisible(true);
	m_ground->AddComponent<TagComponent>("Ground");


	m_ground2 = CreateEntity();
	m_ground2->AddComponent<BoxCollider>(150, 5)->SetVisible(true);
	m_ground2->AddComponent<TagComponent>("Ground");

	m_ground3 = CreateEntity();
	m_ground3->AddComponent<BoxCollider>(150, 5)->SetVisible(true);
	m_ground3->AddComponent<TagComponent>("Ground");


	m_wall = CreateEntity();
	m_wall->AddComponent<BoxCollider>(50, 1080)->SetVisible(true);

	m_wall2 = CreateEntity();
	m_wall2->AddComponent<BoxCollider>(50, 1080)->SetVisible(true);


	m_wall3 = CreateEntity();
	m_wall3->AddComponent<BoxCollider>(5, 150)->SetVisible(true);

	m_wall4 = CreateEntity();
	m_wall4->AddComponent<BoxCollider>(5, 150)->SetVisible(true);

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

	m_ground->GetComponent<TransformComponent>()->SetPos({ 960,1105 });
	m_ground2->GetComponent<TransformComponent>()->SetPos({ 75,930 });
	m_ground3->GetComponent<TransformComponent>()->SetPos({ 1845,930 });

	m_wall->GetComponent<TransformComponent>()->SetPos({ -25,540 });

	m_wall2->GetComponent<TransformComponent>()->SetPos({ 1945,540 });
	m_wall3->GetComponent<TransformComponent>()->SetPos({ 150,1005 });
	m_wall4->GetComponent<TransformComponent>()->SetPos({ 1920-150,1005 });
	
}

void MainScene::Exit()
{
}
