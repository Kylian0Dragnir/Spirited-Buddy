#include "LevelScene.h"
#include "AllComponent.h"
#include "Entity.h"
#include "PlayerMovement.h"
#include "Lib2D/InputManager.h"
#include "AiMovement.h"
#include "ScoreManager.h"
#include "GoalComponent.h"
#include "BallLogic.h"

LevelScene::LevelScene()
{
	m_backGround = CreateEntity();
	m_backGround->AddComponent<SpriteRenderer>()->Load("../../Assets/origbig.png");
	m_backGround->GetComponent<TransformComponent>()->SetScale(3);

	m_wall1 = CreateEntity();
	m_wall1->AddComponent<SpriteRenderer>()->Load("../../Assets/wall.jpg");
	m_wall1->AddComponent<BoxCollider>(1300, 75);
	m_wall1->AddComponent<TagComponent>("WALL1");

	m_wall2 = CreateEntity();
	m_wall2->AddComponent<SpriteRenderer>()->Load("../../Assets/wall.jpg");
	m_wall2->AddComponent<BoxCollider>(1300, 75);
	m_wall2->AddComponent<TagComponent>("WALL2");

	m_ball = CreateEntity(); 
	m_ball->AddComponent<CircleCollider>(20);
	m_ball->AddComponent<SpriteRenderer>()->Load("../../Assets/ballon.png");
	m_ball->AddComponent<Rigidbody2D>()->SetRestitution(1);
	m_ball->AddComponent<TagComponent>("BALL");
	m_ball->GetComponent<TransformComponent>()->SetScale(0.2f);
	m_ball->AddComponent<BallLogic>();
	m_ball->AddComponent<AudioSource>();
	
	m_player = CreateEntity();
	m_player->AddComponent<SpriteRenderer>()->Load("../../Assets/plateforme1.png");
	m_player->GetComponent<TransformComponent>()->SetScale(0.5f);
	m_player->AddComponent<BoxCollider>(50, 180);
	m_player->AddComponent<PlayerMovement>(Key::KEY_z, Key::KEY_s);
	m_player->AddComponent<TagComponent>("ROCK");

	m_scoreManager = CreateEntity();
	m_scoreManager->AddComponent<TextComponent>("../../Assets/Bungee-Regular.otf", 100);
	m_scoreManager->AddComponent<ScoreManager>();
	m_scoreManager->AddComponent<TagComponent>("SCORE_MANAGER");

	m_rightGoal = CreateEntity();
	m_rightGoal->AddComponent<BoxCollider>(10, 800);
	m_rightGoal->AddComponent<TagComponent>("RIGHT_GOAL");
	m_rightGoal->AddComponent<GoalComponent>();
	
	m_leftGoal = CreateEntity();
	m_leftGoal->AddComponent<BoxCollider>(10, 800);
	m_leftGoal->AddComponent<TagComponent>("LEFT_GOAL");
	m_leftGoal->AddComponent<GoalComponent>();

	m_player2 = nullptr;
	m_ai = nullptr;

	m_multiplayer = false;
}

void LevelScene::SetMultiplayer(bool _multi)
{
	m_multiplayer = _multi;
}

void LevelScene::Enter()
{
	m_backGround->GetComponent<TransformComponent>()->SetPos({ 650, 400 });
	m_wall1->GetComponent<TransformComponent>()->SetPos({ 650, 37.5f });
	m_wall2->GetComponent<TransformComponent>()->SetPos({ 650, 762.5f });
	m_ball->GetComponent<TransformComponent>()->SetPos({ 650, 400});
	m_player->GetComponent<TransformComponent>()->SetPos({ 50, 400 });
	m_scoreManager->GetComponent<TransformComponent>()->SetPos({ 650, 35 });
	m_scoreManager->GetComponent<ScoreManager>()->Reset();
	m_rightGoal->GetComponent<TransformComponent>()->SetPos({ 1300, 400 });
	m_leftGoal->GetComponent<TransformComponent>()->SetPos({ 0, 400 });

	if(m_player2 == nullptr && m_ai == nullptr)
	{
		if (m_multiplayer)
		{
			m_player2 = CreateEntity();
			m_player2->AddComponent<SpriteRenderer>()->Load("../../Assets/plateforme2.png");
			m_player2->AddComponent<BoxCollider>(50, 180);
			m_player2->AddComponent<PlayerMovement>(Key::KEY_o, Key::KEY_l);
			m_player2->AddComponent<TagComponent>("ROCK");
			TransformComponent* tc = m_player2->GetComponent<TransformComponent>();
			tc->SetPos({ 1250, 400 });
			tc->SetScale(0.5f);
		}
		else
		{
			m_ai = CreateEntity();
			m_ai->AddComponent<SpriteRenderer>()->Load("../../Assets/plateforme2.png");
			m_ai->AddComponent<BoxCollider>(50, 180);
			m_ai->AddComponent<AiMovement>();
			m_ai->AddComponent<TagComponent>("ROCK");
			TransformComponent* tc = m_ai->GetComponent<TransformComponent>();
			tc->SetPos({ 1250, 400 });
			tc->SetScale(0.5f);
		}
	}
}

void LevelScene::Exit()
{
	if (m_player2)
	{
		DestroyEntityNow(m_player2);
	}

	if (m_ai)
	{
		DestroyEntityNow(m_ai);
	}

	m_player2 = nullptr;
	m_ai = nullptr;
}
