#include "DummyPortalLogic.h"
#include "Lib2D/InputManager.h"
#include "SpriteRenderer.h"
#include "Entity.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "TagComponent.h"
#include "TransformComponent.h"
#include "Rigidbody2D.h"
#include "AScene.h"
#include "SceneManager.h"
#include "TilemapLoader.h"
#include "PossessionLogic.h"
#include "AnimatorComponent.h"
#include "Lib2D/AudioEngine.h"
#include "param.h"

DummyPortalLogic::DummyPortalLogic()
{
	AudioEngine::Get().PlaySound("PORTAL_OPEN", false, 10);
}

void DummyPortalLogic::Update(float dt)
{
	SpriteRenderer* sr = m_owner->GetComponent<SpriteRenderer>();
	CircleCollider* cc = m_owner->GetComponent<CircleCollider>();

	switch (m_state)
	{
	case DummyPortalState::Hidden:
		sr->SetFrame(64, 64, m_frameX, m_frameY);
		sr->SetVisible(false);
		cc->SetActive(true);
		break;

	case DummyPortalState::Appearing:
		HandleAppear(dt);
		break;

	case DummyPortalState::Idle:
		sr->SetVisible(true);
		cc->SetActive(true);
		m_player->GetComponent<TransformComponent>()->SetPos(m_owner->GetComponent<TransformComponent>()->GetPos());

		if (m_timer > 0)
		{
			m_timer -= dt;
			return;
		}
		AudioEngine::Get().PlaySound("PORTAL_CLOSE", false, 10);
		m_state = DummyPortalState::Disappearing;
		break;

	case DummyPortalState::Disappearing:
		HandleDisappear(dt);
		break;
	}
}

void DummyPortalLogic::OnCollisionStay(Collider* _self, Collider* _other)
{
	if (m_player)
		return;

	if(_other->GetOwner()->GetComponent<TagComponent>()->Is("Player"))
		m_player = _other->GetOwner();
}

void DummyPortalLogic::HandleAppear(float _dt)
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

	if (m_frameX <= 0 && m_player)
	{
		m_player->GetComponent<AnimatorComponent>()->Play("Respawn");
		m_timer = 1.f;
		m_state = DummyPortalState::Idle;
	}
}

void DummyPortalLogic::HandleDisappear(float _dt)
{
	if (m_player->GetComponent<AnimatorComponent>()->IsPlaying("Despawn2"))
		return;

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
		m_state = DummyPortalState::Hidden;
		SceneManager::GetInstance().GetCurrentScene()->DestroyEntity(m_owner);
		return;
	}
}

