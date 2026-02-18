#include "SpiritMovement.h"
#include "Lib2D/InputManager.h"
#include "SceneManager.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Rigidbody2D.h"
#include "Collider.h"
#include "Entity.h"
#include "Player.h"
#include "MainScene.h"
#include <iostream>

SpiritMovement::SpiritMovement(Key _switchKey)
{
	m_switchKey = _switchKey;
	m_speed = 1.2f;
	m_player = nullptr;

	m_onCollisionWithPossedable = false;
}

void SpiritMovement::Update(float _dt)
{
	MainScene* cs = static_cast<MainScene*>(SceneManager::GetInstance().GetCurrentScene());
	InputManager& im = InputManager::Get();
	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
	Rigidbody2D* rb = m_owner->GetComponent<Rigidbody2D>();

	if (m_player == nullptr)
		m_player = cs->FindByTag("Player");

	if (m_player == nullptr)
		return;

	if (im.IsKeyDown(m_switchKey))
	{
		if (cs->GetMode() == false) 
		{
			cs->SwitchMode();

			Vector2f targetPos = m_player->GetComponent<TransformComponent>()->GetPos() + Vector2f{ 0, -40 };
			transform->SetPos(targetPos);

			BoxCollider* bc = m_owner->GetComponent<BoxCollider>();
			bc->SetVisible(true);
			bc->SetActive(true);

			CircleCollider* cc = m_owner->GetComponent<CircleCollider>();
			cc->SetVisible(true);
			cc->SetActive(true);
		}
		else if (cs->GetMode() && m_onCollisionWithPossedable)
		{
			cs->SwitchMode();

			BoxCollider* bc = m_owner->GetComponent<BoxCollider>();
			bc->SetVisible(false);
			bc->SetActive(false);

			CircleCollider* cc = m_owner->GetComponent<CircleCollider>();
			cc->SetVisible(false);
			cc->SetActive(false);
		}
	}

	if (cs->GetMode() == false)
		return;

	Vector2f delta = im.GetMouseDelta();
	float maxDelta = 500.f * _dt;

	if (delta.Length() > maxDelta)
	{
		delta = delta.Normalize() * maxDelta;
	}

	rb->SetVelocity(delta / _dt);
}

void SpiritMovement::OnCollisionEnter(Collider* _self, Collider* _other)
{
	TagComponent* otherTag = _other->GetOwner()->GetComponent<TagComponent>();

	if (otherTag == nullptr)
		return;

	if (_self->IsTrigger() && otherTag->Is("Player"))
		m_onCollisionWithPossedable = true;
}

void SpiritMovement::OnCollisionStay(Collider* _self, Collider* _other)
{

}

void SpiritMovement::OnCollisionExit(Collider* _self, Collider* _other)
{
	TagComponent* otherTag = _other->GetOwner()->GetComponent<TagComponent>();

	if (otherTag == nullptr)
		return;

	if (_self->IsTrigger() && otherTag->Is("Player"))
		m_onCollisionWithPossedable = false;
}
