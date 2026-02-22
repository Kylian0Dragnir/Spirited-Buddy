#include "StartScene.h"
#include "AllComponent.h"
#include "Entity.h"
#include "UIButtonLogic.h"
#include "MouseCursorLogic.h"
#include "SceneManager.h"
#include "Application.h"
#include "Lib2D/AudioEngine.h"

#include <iostream>

void StartScene::Enter()
{
	//LOGO
	{
		Entity* ent = CreateEntity();

		ent->AddComponent<SpriteRenderer>()->Load("./Assets/logo.png");

		ent->AddComponent<TagComponent>("BUTTON");

		TransformComponent* transform = ent->GetComponent<TransformComponent>();
		transform->SetScale({ 0.4f, 0.4f });
		transform->SetPos({ 965, 200 });
	}

	// Dialogue Box
	{
		Entity* ent = CreateEntity();

		TransformComponent* transform = ent->GetComponent<TransformComponent>();
		transform->SetPos({ 960, 540 });
		transform->SetScale({ 10, 10 });

		ent->AddComponent<TagComponent>("CONTROLS_BOX");

		SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
		sr->Load("./Assets/dialogue_box.png");
		sr->SetVisible(false);

		TextComponent* text = ent->AddComponent<TextComponent>("./Assets/Bungee-Regular.otf", 35);
		text->SetText("                   CONTROLS\n\nPlayer Movement : AD\n\nPlayer Jump : Space\n\nInteract : E\n\nSpirit Movement : Mouse\n\nSpirit Possess/UnPossess: C\n\nPossessed Physic Object : AD\n\nPause Menu : Escape");
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
			sr->Load("./Assets/close_button.png");
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
						if(BoxCollider* bc = button->GetComponent<BoxCollider>()) bc->SetActive(true);
						button->GetComponent<SpriteRenderer>()->SetVisible(true);
						if(TextComponent* text = button->GetComponent<TextComponent>()) text->SetVisible(true);
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

		//Music Button
		{
			Entity* text = CreateEntity();

			text->AddComponent<TagComponent>("");

			text->AddComponent<TextComponent>("./Assets/Bungee-Regular.otf", 35)->SetText("MUSIC : ");
			text->GetComponent<TransformComponent>()->SetPos({250, 450});


			Entity* ent = CreateEntity();

			TransformComponent* transform = ent->GetComponent<TransformComponent>();
			transform->SetPos({ 420, 450 });
			transform->SetScale({ 2, 2 });

			ent->AddComponent<TagComponent>("BUTTON");

			SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
			sr->Load("./Assets/UIbutton.png");
			sr->SetFrame(100, 35, 200, 0);

			ent->AddComponent<BoxCollider>(175.f, 60.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetTrigger(true);

			ent->AddComponent<TextComponent>("./Assets/Bungee-Regular.otf", 35)->SetText("ON");

			ent->AddComponent<UIButtonLogic>()->SetOnClick([ent]()
				{
					Application& app = Application::Get();
					app.SetMute(!app.GetMute());

					std::string output;

					if (app.GetMute())
					{
						output = "OFF";
						AudioEngine::Get().PlayMusic("MAIN", true);
					}
					else
					{
						output = "ON";
						AudioEngine::Get().PlayMusic("MAIN", true);
					}

					ent->GetComponent<TextComponent>()->SetText(output);
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
		sr->Load("./Assets/UIbutton.png");
		sr->SetFrame(100, 35, 200, 0);

		ent->AddComponent<BoxCollider>(370.f, 120.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetTrigger(true);

		ent->AddComponent<TextComponent>("./Assets/Bungee-Regular.otf", 48)->SetText("START");

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
		sr->Load("./Assets/UIbutton.png");
		sr->SetFrame(100, 35, 200, 0);

		ent->AddComponent<BoxCollider>(370.f, 120.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetTrigger(true);

		ent->AddComponent<TextComponent>("./Assets/Bungee-Regular.otf", 48)->SetText("CONTROLS");

		ent->AddComponent<UIButtonLogic>()->SetOnClick([this]()
			{
				std::vector<Entity*> buttons = FindAllEntitiesWithTag("BUTTON");

				for (Entity* button : buttons)
				{
					if (BoxCollider* bc = button->GetComponent<BoxCollider>()) bc->SetActive(false);
					button->GetComponent<SpriteRenderer>()->SetVisible(false);
					if (TextComponent* text = button->GetComponent<TextComponent>()) text->SetVisible(false);
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

	// Control Button
	{
		Entity* ent = CreateEntity();

		TransformComponent* transform = ent->GetComponent<TransformComponent>();
		transform->SetPos({ 960, 750 });
		transform->SetScale({ 4, 4 });

		ent->AddComponent<TagComponent>("BUTTON");

		SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
		sr->Load("./Assets/UIbutton.png");
		sr->SetFrame(100, 35, 200, 0);

		ent->AddComponent<BoxCollider>(370.f, 120.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetTrigger(true);

		TextComponent* text = ent->AddComponent<TextComponent>("./Assets/Bungee-Regular.otf", 30);
		text->SetText("         GO TO\nLEVEL SELECT");
		text->SetOffset({ 385.f , 0.f });

		ent->AddComponent<UIButtonLogic>()->SetOnClick([this]()
			{
				SceneManager::GetInstance().ChangeScene("LevelSelectorScene");
			});
	}

	// Quit Button
	{
		Entity* ent = CreateEntity();

		TransformComponent* transform = ent->GetComponent<TransformComponent>();
		transform->SetPos({ 960, 900 });
		transform->SetScale({ 4, 4 });

		ent->AddComponent<TagComponent>("BUTTON");

		SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
		sr->Load("./Assets/UIbutton.png");
		sr->SetFrame(100, 35, 200, 0);

		ent->AddComponent<BoxCollider>(370.f, 120.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetTrigger(true);

		ent->AddComponent<TextComponent>("./Assets/Bungee-Regular.otf", 48)->SetText("QUIT");

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
		sr->Load("./Assets/Spirit_backup.png");
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