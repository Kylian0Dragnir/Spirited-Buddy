#include "PortalLogic.h"
#include "Lib2D/InputManager.h"
#include "SpriteRenderer.h"
#include "Entity.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "TagComponent.h"
#include "Rigidbody2D.h"
#include "SceneManager.h"
#include "MainScene.h"
#include "TilemapLoader.h"

PortalLogic::PortalLogic(const std::string& _nextSceneID)
{
	m_nextSceneID = _nextSceneID;
}

void PortalLogic::Update(float dt)
{
	SpriteRenderer* sr = m_owner->GetComponent<SpriteRenderer>();
	CircleCollider* cc = m_owner->GetComponent<CircleCollider>();

	switch (m_state)
	{
	case PortalState::Hidden:
		sr->SetFrame(64, 64, m_frameX, m_frameY);
		sr->SetVisible(false);
		cc->SetActive(false);
		cc->SetVisible(false);
		break;

	case PortalState::Appearing:
		HandleAppear(dt);
		break;

	case PortalState::Idle:
		sr->SetVisible(true);
		cc->SetActive(true);
		cc->SetVisible(true);
		break;

	case PortalState::Disappearing:
		HandleDisappear(dt);
		break;
	}
}

void PortalLogic::OnCollisionStay(Collider* _self, Collider* _other)
{
	TagComponent* tags = _other->GetOwner()->GetComponent<TagComponent>();

	if (tags == nullptr)
		return;

	if (InputManager::Get().IsKeyDown(Key::KEY_e) && tags->Is("Player") && tags->Is("POSSESSED"))
	{
		m_state = PortalState::Disappearing;
		m_timer = 0.f;
	}
}

void PortalLogic::Appear()
{
	if (m_state != PortalState::Hidden)
		return;

	m_state = PortalState::Appearing;
}

void PortalLogic::HandleAppear(float _dt)
{
	SpriteRenderer* sr = m_owner->GetComponent<SpriteRenderer>();
	sr->SetVisible(true);

	if (m_timer > 0)
	{
		m_timer -= _dt;
		return;
	}

	m_timer = 0.07f;

	m_frameX -= 64;
	sr->SetFrame(64, 64, m_frameX, m_frameY);

	if (m_frameX <= 0)
	{
		m_state = PortalState::Idle;
	}
}

void PortalLogic::HandleDisappear(float _dt)
{
	SpriteRenderer* sr = m_owner->GetComponent<SpriteRenderer>();

	if (m_timer > 0)
	{
		m_timer -= _dt;
		return;
	}

	m_timer = 0.07f;

	m_frameX += 64;
	sr->SetFrame(64, 64, m_frameX, m_frameY);

	if (m_frameX >= 512)
	{
		m_state = PortalState::Hidden;
		SceneManager::GetInstance().ChangeScene(m_nextSceneID);
		return;
	}
}

