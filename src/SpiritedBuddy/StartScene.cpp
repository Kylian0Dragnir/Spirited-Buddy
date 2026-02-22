#include "StartScene.h"
#include "AllComponent.h"
#include "Entity.h"
#include "UIButtonLogic.h"
#include "MouseCursorLogic.h"
#include "SceneManager.h"
#include "Application.h"


#include <iostream>

void StartScene::Enter()
{
	// Dialogue Box
	{
		Entity* ent = CreateEntity();

		TransformComponent* transform = ent->GetComponent<TransformComponent>();
		transform->SetPos({ 960, 540 });
		transform->SetScale({ 10, 10 });

		ent->AddComponent<TagComponent>("CONTROLS_BOX");

		SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
		sr->Load("../../Assets/dialogue_box.png");
		sr->SetVisible(false);

		TextComponent* text = ent->AddComponent<TextComponent>("../../Assets/Bungee-Regular.otf", 35);
		text->SetText("                   CONTROLS\n\nPlayer Movement : QD\n\nPlayer Jump : Space\n\nInteract : E\n\nSpirit Movement : Mouse\n\nSpirit Possess/UnPossess: C\n\nPossessed Physic Object : QD\n\nPause Menu : Escape");
		text->SetOffset({ 240.f, 0.f });
		text->SetVisible(false);

		//Close Button
		{
			Entity* ent = CreateEntity();

			TransformComponent* transform = ent->GetComponent<TransformComponent>();
			transform->SetPos({ 1450, 200 });
			transform->SetScale({ 3, 3 });

			ent->AddComponent<TagComponent>("CONTROLS_BOX");

			SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
			sr->Load("../../Assets/close_button.png");
			sr->SetFrame(32, 32, 0, 0);
			sr->SetVisible(false);

			BoxCollider* bc = ent->AddComponent<BoxCollider>(100.f, 100.f, SPIRIT_LAYER, SPIRIT_LAYER);
			bc->SetTrigger(true);
			bc->SetActive(false);

			ent->AddComponent<UIButtonLogic>()->SetOnClick([this]()
				{
					std::vector<Entity*> buttons = FindAllEntitiesWithTag("BUTTON");

					for (Entity* button : buttons)
					{
						button->GetComponent<BoxCollider>()->SetActive(true);
						button->GetComponent<SpriteRenderer>()->SetVisible(true);
						button->GetComponent<TextComponent>()->SetVisible(true);
					}

					std::vector<Entity*> controlsBox = FindAllEntitiesWithTag("CONTROLS_BOX");

					for (Entity* ent : controlsBox)
					{
						ent->GetComponent<SpriteRenderer>()->SetVisible(false);
						if(TextComponent* text = ent->GetComponent<TextComponent>()) text->SetVisible(false);
						if (BoxCollider* bc = ent->GetComponent<BoxCollider>()) bc->SetActive(false);
					}
				});
		}
	}



	// START Button
	{
		Entity* ent = CreateEntity();

		TransformComponent* transform = ent->GetComponent<TransformComponent>();
		transform->SetPos({ 960, 450 });
		transform->SetScale({ 4, 4 });

		ent->AddComponent<TagComponent>("BUTTON");

		SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
		sr->Load("../../Assets/UIbutton.png");
		sr->SetFrame(100, 35, 200, 0);

		ent->AddComponent<BoxCollider>(370.f, 120.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetTrigger(true);

		ent->AddComponent<TextComponent>("../../Assets/Bungee-Regular.otf", 48)->SetText("START");

		ent->AddComponent<UIButtonLogic>()->SetOnClick([this]()
			{
				SceneManager::GetInstance().ChangeScene("Level1Scene");
			});
	}

	// Control Button
	{
		Entity* ent = CreateEntity();

		TransformComponent* transform = ent->GetComponent<TransformComponent>();
		transform->SetPos({ 960, 600 });
		transform->SetScale({ 4, 4 });

		ent->AddComponent<TagComponent>("BUTTON");

		SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
		sr->Load("../../Assets/UIbutton.png");
		sr->SetFrame(100, 35, 200, 0);

		ent->AddComponent<BoxCollider>(370.f, 120.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetTrigger(true);

		ent->AddComponent<TextComponent>("../../Assets/Bungee-Regular.otf", 48)->SetText("CONTROLS");

		ent->AddComponent<UIButtonLogic>()->SetOnClick([this]()
			{
				std::vector<Entity*> buttons = FindAllEntitiesWithTag("BUTTON");

				for (Entity* button : buttons)
				{
					button->GetComponent<BoxCollider>()->SetActive(false);
					button->GetComponent<SpriteRenderer>()->SetVisible(false);
					button->GetComponent<TextComponent>()->SetVisible(false);
				}

				Entity* controlBox = FindByTag("CONTROLS_BOX");

				std::vector<Entity*> controlsBox = FindAllEntitiesWithTag("CONTROLS_BOX");

				for (Entity* ent : controlsBox)
				{
					ent->GetComponent<SpriteRenderer>()->SetVisible(true);
					if (TextComponent* text = ent->GetComponent<TextComponent>()) text->SetVisible(true);
					if (BoxCollider* bc = ent->GetComponent<BoxCollider>()) bc->SetActive(true);
				}
			});
	}

	// Quit Button
	{
		Entity* ent = CreateEntity();

		TransformComponent* transform = ent->GetComponent<TransformComponent>();
		transform->SetPos({ 960, 750 });
		transform->SetScale({ 4, 4 });

		ent->AddComponent<TagComponent>("BUTTON");

		SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
		sr->Load("../../Assets/UIbutton.png");
		sr->SetFrame(100, 35, 200, 0);

		ent->AddComponent<BoxCollider>(370.f, 120.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetTrigger(true);

		ent->AddComponent<TextComponent>("../../Assets/Bungee-Regular.otf", 48)->SetText("QUIT");

		ent->AddComponent<UIButtonLogic>()->SetOnClick([this]()
			{
				Application::Get().ShutDownApp();
			});
	}

	// Mouse Cursor
	{
		m_mouse = CreateEntity();
		m_mouse->AddComponent<TagComponent>("");

		TransformComponent* transform = m_mouse->GetComponent<TransformComponent>();
		transform->SetPos({ 1200, 600 });
		transform->SetRotationCenter({ 32,48 });
		transform->SetRotation(-45);
		transform->SetScale({ 3.f, 3.f });

		SpriteRenderer* sr = m_mouse->AddComponent<SpriteRenderer>();
		sr->Load("../../Assets/Spirit_backup.png");
		sr->SetOffset({ 25, 30 });

		//Solid Collider
		m_mouse->AddComponent<CircleCollider>(15.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetVisible(false);

		m_mouse->AddComponent<Rigidbody2D>(1.0f, false, 0.f);

		m_mouse->AddComponent<MouseCursorLogic>();
	}
}

void StartScene::Update(float _dt)
{
	//std::cout << m_mouse->GetComponent<TransformComponent>()->GetPos().GetX() << " " << m_mouse->GetComponent<TransformComponent>()->GetPos().GetY() << std::endl;
	AScene::Update(0.001f);
}
void StartScene::Exit()
{
	DestroyAllEntities();
	m_mouse = nullptr;
}