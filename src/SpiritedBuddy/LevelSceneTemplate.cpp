#include "LevelSceneTemplate.h"
#include "AllComponent.h"
#include "Entity.h"
#include "PlayerMovement.h"
#include "SpiritLogic.h"
#include "PhysicObjectMovement.h" 
#include "CollectibleLogic.h"
#include "PossessionLogic.h"
#include "PortalLogic.h"
#include "ButtonLogic.h"
#include "DummyWallLogic.h"
#include "WorldWrapLogic.h"
#include "Collider.h"
#include "UIButtonLogic.h"
#include "MouseCursorLogic.h"
#include "Lib2D/InputManager.h"
#include "TilemapLoader.h"
#include "SceneManager.h"
#include "Application.h"
#include "CollisionSystem.h"
#include "Lib2D/AudioEngine.h"

#include <iostream>

LevelSceneTemplate::LevelSceneTemplate()
{
	m_player = nullptr;
	m_spirit = nullptr;
	m_onPause = false;
}

LevelSceneTemplate::~LevelSceneTemplate()
{
	for (Entity* ent : m_pauseMenuEntities)
	{
		delete ent;
	}
}

void LevelSceneTemplate::Enter()
{
	m_onPause = false;

	// Dialogue Box
	{
		Entity* ent = new Entity;

		TransformComponent* transform = ent->AddComponent<TransformComponent>();
		transform->SetPos({ 960, 540 });
		transform->SetScale({ 10, 10 });

		ent->AddComponent<TagComponent>("");

		ent->AddComponent<SpriteRenderer>()->Load("./Assets/dialogue_box.png");

		TextComponent* text = ent->AddComponent<TextComponent>("./Assets/Bungee-Regular.otf", 48);
		text->SetText("MENU");
		text->SetOffset({ 0.f, -300.f });

		m_pauseMenuEntities.push_back(ent);
	}

	// Continue Button
	{
		Entity* ent = new Entity;

		TransformComponent* transform = ent->AddComponent<TransformComponent>();
		transform->SetPos({ 960, 350 });
		transform->SetScale({ 4, 4 });

		ent->AddComponent<TagComponent>("");

		SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
		sr->Load("./Assets/UIbutton.png");
		sr->SetFrame(100, 35, 200, 0);

		ent->AddComponent<BoxCollider>(370.f, 120.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetTrigger(true);

		ent->AddComponent<TextComponent>("./Assets/Bungee-Regular.otf", 48)->SetText("CONTINUE");

		ent->AddComponent<UIButtonLogic>()->SetOnClick([this]()
			{
				m_onPause = false;
			});

		m_pauseMenuEntities.push_back(ent);
	}

	// Restart Button
	{
		Entity* ent = new Entity;

		TransformComponent* transform = ent->AddComponent<TransformComponent>();
		transform->SetPos({ 960, 475 });
		transform->SetScale({ 4, 4 });

		ent->AddComponent<TagComponent>("");

		SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
		sr->Load("./Assets/UIbutton.png");
		sr->SetFrame(100, 35, 200, 0);

		ent->AddComponent<BoxCollider>(370.f, 120.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetTrigger(true);

		ent->AddComponent<TextComponent>("./Assets/Bungee-Regular.otf", 48)->SetText("RESTART");

		ent->AddComponent<UIButtonLogic>()->SetOnClick([this]()
			{
				m_onPause = false;
				m_player->GetComponent<AnimatorComponent>()->Play("Despawn");
				AudioEngine::Get().PlaySound("DEATH", false);
			});

		m_pauseMenuEntities.push_back(ent);
	}

	// Return to Start Button
	{
		Entity* ent = new Entity;

		TransformComponent* transform = ent->AddComponent<TransformComponent>();
		transform->SetPos({ 960, 600 });
		transform->SetScale({ 4, 4 });

		ent->AddComponent<TagComponent>("");

		SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
		sr->Load("./Assets/UIbutton.png");
		sr->SetFrame(100, 35, 200, 0);

		ent->AddComponent<BoxCollider>(370.f, 120.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetTrigger(true);

		TextComponent* text = ent->AddComponent<TextComponent>("./Assets/Bungee-Regular.otf", 30);
		text->SetText(" RETURN\nTO START");
		text->SetOffset({ 425.f , 0.f });

		ent->AddComponent<UIButtonLogic>()->SetOnClick([this]()
			{
				SceneManager::GetInstance().ChangeScene("StartScene");
			});

		m_pauseMenuEntities.push_back(ent);
	}

	// GO to level select Button
	{
		Entity* ent = new Entity;

		TransformComponent* transform = ent->AddComponent<TransformComponent>();
		transform->SetPos({ 960, 725 });
		transform->SetScale({ 4, 4 });

		ent->AddComponent<TagComponent>("");

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

		m_pauseMenuEntities.push_back(ent);
	}

	// Quit Button
	{
		Entity* ent = new Entity;

		TransformComponent* transform = ent->AddComponent<TransformComponent>();
		transform->SetPos({ 960, 850 });
		transform->SetScale({ 4, 4 });

		ent->AddComponent<TagComponent>("");

		SpriteRenderer* sr = ent->AddComponent<SpriteRenderer>();
		sr->Load("./Assets/UIbutton.png");
		sr->SetFrame(100, 35, 200, 0);

		ent->AddComponent<BoxCollider>(370.f, 120.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetTrigger(true);

		ent->AddComponent<TextComponent>("./Assets/Bungee-Regular.otf", 48)->SetText("QUIT");

		ent->AddComponent<UIButtonLogic>()->SetOnClick([this]()
			{
				Application::Get().ShutDownApp();
			});

		m_pauseMenuEntities.push_back(ent);
	}

	// Mouse Cursor
	{
		m_mouse = new Entity;
		m_mouse->AddComponent<TagComponent>("");

		TransformComponent* transform = m_mouse->AddComponent<TransformComponent>();
		transform->SetPos({ 960, 540 });
		transform->SetRotationCenter({ 32,48 });
		transform->SetRotation(-45);
		transform->SetScale({ 3.f, 3.f });

		SpriteRenderer* sr = m_mouse->AddComponent<SpriteRenderer>();
		sr->Load("./Assets/Spirit_backup.png");
		sr->SetOffset({ 25, 30 });

		//Solid Collider
		m_mouse->AddComponent<CircleCollider>(15.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetVisible(false);

		m_mouse->AddComponent<MouseCursorLogic>();

		m_mouse->AddComponent<Rigidbody2D>(1.0f, false, 0.f);

		m_pauseMenuEntities.push_back(m_mouse);
	}

	OnEnter();
}

void LevelSceneTemplate::Update(float _dt)
{
	if (InputManager::Get().IsKeyDown(Key::KEY_ESCAPE))
	{
		m_mouse->GetComponent<TransformComponent>()->SetPos({ 1200, 600 });
		m_onPause = !m_onPause;
	}

	if (m_onPause)
	{
		UpdatePauseMenu(_dt);
		return;
	}

	AScene::Update(_dt);

	CleanDestroyedEntities();

	if (m_collectibles.empty())
	{
		for (Entity* p : m_portals)
		{
			p->GetComponent<PortalLogic>()->Appear();
		}
	}

	OnUpdate(_dt);
}

void LevelSceneTemplate::Draw(Window* window)
{
	AScene::Draw(window);

	if(m_onPause)
	{
		for (Entity* entity : m_pauseMenuEntities)
		{
			entity->Draw(window);
		}
	}
}

void LevelSceneTemplate::Exit()
{
	DestroyAllEntities();

	AudioEngine::Get().StopAllSounds();

	CleanVectors();

	OnExit();
}

void LevelSceneTemplate::UpdatePauseMenu(float _dt)
{
	CollisionSystem::GetInstance().Update(m_pauseMenuEntities);

	for (Entity* ent : m_pauseMenuEntities)
	{
		ent->Update(_dt);
	}
}

void LevelSceneTemplate::CreateCollectible(Vector2f _pos)
{
	Entity* coin = CreateEntity();

	coin->AddComponent<BoxCollider>(25.f, 25.f, ENV_LAYER, SPIRIT_LAYER | PLAYER_LAYER)->SetTrigger(true);

	coin->AddComponent<TagComponent>("COLLECTIBLE");

	SpriteRenderer* sr = coin->AddComponent<SpriteRenderer>();
	sr->Load("./Assets/collectible.png");
	sr->SetFrame(32, 32, 0, 0);

	coin->AddComponent<CollectibleLogic>();
	coin->GetComponent<TransformComponent>()->SetPos(_pos);

	AnimatorComponent* animator = coin->AddComponent<AnimatorComponent>();

	Animation idle;
	idle.frameWidth = 32;
	idle.frameHeight = 32;
	idle.frameDuration = 0.1f;
	idle.loop = true;

	for (int i = 0; i < 7; i++)
		idle.frames.push_back({ (float)i , 0.f });

	animator->AddAnimation("Idle", idle);

	animator->Play("Idle");

	m_collectibles.push_back(coin);
}

void LevelSceneTemplate::CreatePlayer(Vector2f _pos)
{
	m_player = CreateEntity();
	SpriteRenderer* sr = m_player->AddComponent<SpriteRenderer>();
	sr->Load("./Assets/Player/player_sheet.png");
	sr->SetFrame(32, 32, 128, 0);
	m_player->AddComponent<TagComponent>("Player");

	//Solid Collider
	m_player->AddComponent<BoxCollider>(33.75f, 50.f, PLAYER_LAYER, PLAYER_LAYER | ENV_LAYER | SPIRIT_LAYER)->SetVisible(false);

	//Grounded Trigger Collider
	BoxCollider* bc = m_player->AddComponent<BoxCollider>(33.75f / 2, 1, PLAYER_LAYER, PLAYER_LAYER | ENV_LAYER);
	bc->SetVisible(false);
	bc->SetTrigger(true);
	bc->SetOffset(0, 30);

	m_player->AddComponent<PossessionLogic>()->SetPossessed(true);
	m_player->AddComponent<PlayerMovement>(Key::KEY_a, Key::KEY_d, Key::KEY_SPACE);

	m_player->GetComponent<TransformComponent>()->SetPos(_pos);
	m_player->GetComponent<TransformComponent>()->SetScale({1.5f, 1.5f});

	m_player->AddComponent<Rigidbody2D>(1.f, true, 0.f)->SetGravity({ 0.f,1000.f });

	m_player->AddComponent<WorldWrapLogic>()->Generate();

	AnimatorComponent* animator = m_player->AddComponent<AnimatorComponent>();

	//Idle
	{
		Animation idle;
		idle.frameWidth = 32;
		idle.frameHeight = 32;
		idle.frameDuration = 0.3f;
		idle.loop = true;

		idle.frames = {
		{0 , 0 },
		{1 , 0 },
		{0 , 0 },
		{1 , 0 },
		{0 , 1 },
		{1 , 1 }
		};

		animator->AddAnimation("Idle", idle);
	}

	//Walk
	{
		Animation walk;
		walk.frameWidth = 32;
		walk.frameHeight = 32;
		walk.frameDuration = 0.1f;
		walk.loop = true;

		for (int i = 0; i < 8; i++)
			walk.frames.push_back({ (float)i , 3.f });

		animator->AddAnimation("Walk", walk);
	}

	//TakeOff
	{
		Animation takeOff;
		takeOff.frameWidth = 32;
		takeOff.frameHeight = 32;
		takeOff.frameDuration = 0.01f;
		takeOff.loop = false;

		takeOff.frames = {
			{0 , 5 },
			{1 , 5 }
		};

		takeOff.onFinish = [this]()
			{
				m_player->GetComponent<PlayerMovement>()->Jump();
			};

		animator->AddAnimation("TakeOff", takeOff);
	}
	
	//Jump
	{
		Animation jump;
		jump.frameWidth = 32;
		jump.frameHeight = 32;
		jump.frameDuration = 0.2f;
		jump.loop = true;

		jump.frames = {
			{2 , 5 },
			{3 , 5 }
		};

		animator->AddAnimation("Jump", jump);
	}

	//Fall
	{
		Animation fall;
		fall.frameWidth = 32;
		fall.frameHeight = 32;
		fall.frameDuration = 0.2f;
		fall.loop = true;

		fall.frames = {
		{3 , 5 },
		{4 , 5 },
		{5 , 5 }
		};

		animator->AddAnimation("Fall", fall);
	}
	
	//Land
	{
		Animation land;
		land.frameWidth = 32;
		land.frameHeight = 32;
		land.frameDuration = 0.01f;
		land.loop = false;

		land.frames = {
		{6 , 5 },
		{7 , 5 }
		};

		animator->AddAnimation("Land", land);
	}

	//EnterPossession
	{
		Animation enterPossession;
		enterPossession.frameWidth = 32;
		enterPossession.frameHeight = 32;
		enterPossession.frameDuration = 0.1f;
		enterPossession.loop = false;

		for (int i = 3; i >= 0; i--)
			enterPossession.frames.push_back({ (float)i , 4.f });

		animator->AddAnimation("EnterPossession", enterPossession);
	}

	//ExitPossession
	{
		Animation exitPossession;
		exitPossession.frameWidth = 32;
		exitPossession.frameHeight = 32;
		exitPossession.frameDuration = 0.1f;
		exitPossession.loop = false;

		for (int i = 0; i < 4; i++)
			exitPossession.frames.push_back({ (float)i , 4.f});

		animator->AddAnimation("ExitPossession", exitPossession);
	}

	//Despawn
	{
		Animation despawn;
		despawn.frameWidth = 32;
		despawn.frameHeight = 32;
		despawn.frameDuration = 0.1f;
		despawn.loop = false;

		for (int i = 0; i < 5; i++)
			despawn.frames.push_back({ (float)i , 6.f });

		despawn.onFinish = [this]() 
			{
				SceneManager::GetInstance().ReloadScene();
			};

		animator->AddAnimation("Despawn", despawn);
	}

	//Despawn2
	{
		Animation despawnwr;
		despawnwr.frameWidth = 32;
		despawnwr.frameHeight = 32;
		despawnwr.frameDuration = 0.1f;
		despawnwr.loop = false;

		despawnwr.onFinish = [this]()
			{
				m_player->GetComponent<SpriteRenderer>()->SetVisible(false);
			};

		for (int i = 0; i < 4; i++)
			despawnwr.frames.push_back({ (float)i , 6.f });

		animator->AddAnimation("Despawn2", despawnwr);
	}

	//Respawn
	{
		Animation respawn;
		respawn.frameWidth = 32;
		respawn.frameHeight = 32;
		respawn.frameDuration = 0.1f;
		respawn.loop = false;

		for (int i = 3; i >= 0; i--)
			respawn.frames.push_back({ (float)i , 6.f });

		animator->AddAnimation("Respawn", respawn);
	}

	animator->Play("Respawn");
}

void LevelSceneTemplate::CreateSpirit(Vector2f _pos)
{
	m_spirit = CreateEntity();
	m_spirit->AddComponent<TagComponent>("Spirit");

	SpriteRenderer* sr = m_spirit->AddComponent<SpriteRenderer>();
	sr->Load("./Assets/Spirit.png");
	sr->SetFrame(64, 64, 0, 0);
	sr->SetOffset({ 0,-11.25 });
	sr->SetVisible(false);

	//Solid Collider
	m_spirit->AddComponent<CircleCollider>(10.5f, SPIRIT_LAYER, SPIRIT_LAYER | ENV_LAYER)->SetVisible(false);

	//Interaction Trigger Collider
	CircleCollider* cc = m_spirit->AddComponent<CircleCollider>(30.f, SPIRIT_LAYER, SPIRIT_LAYER | PLAYER_LAYER);
	cc->SetVisible(false);
	cc->SetTrigger(true);

	m_spirit->AddComponent<SpiritLogic>(Key::KEY_c,m_player);

	TransformComponent* transform = m_spirit->GetComponent<TransformComponent>();
	transform->SetPos(_pos);
	transform->SetScale({ 0.75f, 0.75f });
	transform->SetRotationCenter({ 24,36 });

	m_spirit->AddComponent<Rigidbody2D>(1.0f, false, 0.f);

	m_spirit->AddComponent<WorldWrapLogic>()->Generate();
}

void LevelSceneTemplate::CreatePortal(Vector2f _pos, const std::string& newSceneID)
{
	Entity* portal = CreateEntity();

	portal->AddComponent<TagComponent>("PORTAL");

	SpriteRenderer* sr = portal->AddComponent<SpriteRenderer>();
	sr->Load("./Assets/Portal-Sheet.png");
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

void LevelSceneTemplate::CreateText(Vector2f _pos, const std::string& _text, int _size, const std::string& _fontPath)
{
	Entity* text = CreateEntity();

	text->AddComponent<TagComponent>("");

	text->AddComponent<TextComponent>(_fontPath, _size)->SetText(_text);
	text->GetComponent<TransformComponent>()->SetPos(_pos);
}

void LevelSceneTemplate::CreateCrate(Vector2f _pos)
{
	Entity* crate = CreateEntity();

	//Solid Collider
	crate->AddComponent<BoxCollider>(40.f, 40.f, PLAYER_LAYER, PLAYER_LAYER | ENV_LAYER | SPIRIT_LAYER)->SetVisible(true);

	crate->AddComponent<SpriteRenderer>()->Load("./Assets/crate.png");

	crate->AddComponent<TagComponent>("CRATE")->AddTag("PhysicObject");

	crate->AddComponent<PossessionLogic>();
	crate->AddComponent<PhysicObjectMovement>(Key::KEY_a, Key::KEY_d);

	TransformComponent* transform = crate->GetComponent<TransformComponent>();
	transform->SetPos(_pos);
	transform->SetScale({ 2.5f, 2.5f });

	crate->AddComponent<Rigidbody2D>(1.f, true, 0.f)->SetGravity({ 0.f,1000.f });

	crate->AddComponent<WorldWrapLogic>()->Generate();
}

ButtonLogic* LevelSceneTemplate::CreateButton(Vector2f _pos, ButtonMode _mode)
{
	Entity* button = CreateEntity();

	TransformComponent* tc = button->GetComponent<TransformComponent>();
	tc->SetScale({ 1.5f,1.5f });

	button->AddComponent<SpriteRenderer>()->Load("./Assets/button.png");
	SpriteRenderer* sr = button->GetComponent<SpriteRenderer>();
	sr->SetFrame(32, 32, 0, 0);

	//Solid Collider
	BoxCollider* solidCollider = button->AddComponent<BoxCollider>(48.f, 4.f, PLAYER_LAYER, PLAYER_LAYER);
	solidCollider->SetOffset(0,22);

	//Trigger Collider
	BoxCollider* triggerCollider = button->AddComponent<BoxCollider>(44.f, 7.f, PLAYER_LAYER, PLAYER_LAYER);
	triggerCollider->SetTrigger(true);
	triggerCollider->SetOffset(0, 17);

	button->AddComponent<TagComponent>("BUTTON")->AddTag("PhysicObject");

	button->GetComponent<TransformComponent>()->SetPos(_pos);

	return button->AddComponent<ButtonLogic>(_mode);
}

void LevelSceneTemplate::CreateDummyWall(Vector2f _pos, const std::string& _direction)
{
	Entity* dummyWall = CreateEntity();

	dummyWall->AddComponent<SpriteRenderer>()->Load("./Assets/" + _direction + "DummyWall.png");
	dummyWall->AddComponent<TagComponent>("");

	BoxCollider* bc = dummyWall->AddComponent<BoxCollider>(160.f, 160.f, ENV_LAYER, PLAYER_LAYER | SPIRIT_LAYER);
	bc->SetVisible(false);
	bc->SetTrigger(true);

	dummyWall->AddComponent<DummyWallLogic>();

	TransformComponent* transform = dummyWall->GetComponent<TransformComponent>();
	transform->SetPos(_pos);
	transform->SetScale({ 2.f, 2.f });
}

void LevelSceneTemplate::CreatePlayerBarrier(Vector2f _start, Vector2f _end, const std::string& _tag)
{
	Entity* barrier = CreateEntity();

	bool vertical = true;

	float height = abs(_end.GetY() - _start.GetY());

	if ( height == 0)
	{
		 height = abs(_end.GetX() - _start.GetX());
		 vertical = false;
	}

	Vector2f center = {
		(_start.GetX() + _end.GetX()) * 0.5f,
		(_start.GetY() + _end.GetY()) * 0.5f
	};

	SpriteRenderer* sr = barrier->AddComponent<SpriteRenderer>();
	sr->Load("./Assets/barrier/red_barrier.png");
	sr->SetFrame(16, 16, 0, 0);
	sr->SetOpacity(255);

	TransformComponent* transform = barrier->GetComponent<TransformComponent>();
	transform->SetPos(center);
	transform->SetScale({ 2.f, 2.f });

	TagComponent* tc = barrier->AddComponent<TagComponent>("PLAYER_BARRIER");
	if (!_tag.empty())
		tc->AddTag(_tag);

	if(vertical)
	{
		sr->SetTiledSize({ 32.f, height });
		barrier->AddComponent<BoxCollider>(32.f, height, PLAYER_LAYER, PLAYER_LAYER)->SetVisible(false);
	}
	else
	{
		tc->AddTag("Ground");
		transform->SetRotationCenter({ 16.f, 16.f });
		transform->SetRotation(-90);
		sr->SetTiledSize({ height , 32.f });
		barrier->AddComponent<BoxCollider>(height, 32.f, PLAYER_LAYER, PLAYER_LAYER)->SetVisible(false);
	}

	AnimatorComponent* animator = barrier->AddComponent<AnimatorComponent>();

	//Idle
	{
		Animation idle;
		idle.frameWidth = 16;
		idle.frameHeight = 16;
		idle.frameDuration = 0.001f;
		idle.loop = true;

		for (int i = 0; i < 16; i++)
			idle.frames.push_back({ (float)i , 0.f});

		animator->AddAnimation("Idle", idle);
	}

	animator->Play("Idle");

	m_playerBarriers.push_back(barrier);
}

void LevelSceneTemplate::CreateSpiritBarrier(Vector2f _start, Vector2f _end, const std::string& _tag)
{
	Entity* barrier = CreateEntity();

	bool vertical = true;

	float height = abs(_end.GetY() - _start.GetY());

	if (height == 0)
	{
		height = abs(_end.GetX() - _start.GetX());
		vertical = false;
	}

	Vector2f center = {
		(_start.GetX() + _end.GetX()) * 0.5f,
		(_start.GetY() + _end.GetY()) * 0.5f
	};

	SpriteRenderer* sr = barrier->AddComponent<SpriteRenderer>();
	sr->Load("./Assets/barrier/green_barrier.png");
	sr->SetFrame(16, 16, 0, 0);
	sr->SetOpacity(255);

	TransformComponent* transform = barrier->GetComponent<TransformComponent>();
	transform->SetPos(center);
	transform->SetScale({ 2.f, 2.f });

	if (vertical)
	{
		sr->SetTiledSize({ 32.f, height });
		barrier->AddComponent<BoxCollider>(32.f, height, SPIRIT_LAYER, SPIRIT_LAYER)->SetVisible(false);
	}
	else
	{
		transform->SetRotationCenter({ 16.f, 16.f });
		transform->SetRotation(-90);
		sr->SetTiledSize({ height , 32.f });
		barrier->AddComponent<BoxCollider>(height, 32.f, SPIRIT_LAYER, SPIRIT_LAYER)->SetVisible(false);
	}

	TagComponent* tc = barrier->AddComponent<TagComponent>("SPIRIT_BARRIER");
	if (!_tag.empty())
		tc->AddTag(_tag);

	AnimatorComponent* animator = barrier->AddComponent<AnimatorComponent>();

	//Idle
	{
		Animation idle;
		idle.frameWidth = 16;
		idle.frameHeight = 16;
		idle.frameDuration = 0.001f;
		idle.loop = true;

		for (int i = 0; i < 16; i++)
			idle.frames.push_back({ (float)i , 0.f });

		animator->AddAnimation("Idle", idle);
	}

	animator->Play("Idle");

	m_spiritBarriers.push_back(barrier);
}

void LevelSceneTemplate::CleanDestroyedEntities()
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

void LevelSceneTemplate::CleanVectors()
{
	m_collectibles.clear();

	m_playerBarriers.clear();

	m_spiritBarriers.clear();

	m_portals.clear();

	m_pauseMenuEntities.clear();
}