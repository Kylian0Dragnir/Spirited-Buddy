#include "SpiritLogic.h"
#include "Lib2D/InputManager.h"
#include "SceneManager.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "PossessionLogic.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "SpriteRenderer.h"
#include "Rigidbody2D.h"
#include "Collider.h"
#include "Entity.h"
#include "AScene.h"
#include <iostream>

SpiritLogic::SpiritLogic(Key _switchKey)
{
	m_switchKey = _switchKey;
	m_speed = 1.2f;

	m_isInPossessionMode = true;
	m_switchCouldown = 0.02f;
}

void SpiritLogic::Update(float _dt)
{
	if (m_switchCouldown > 0)
		m_switchCouldown -= _dt;

	AScene* cs = SceneManager::GetInstance().GetCurrentScene();
	InputManager& im = InputManager::Get();
	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
	Rigidbody2D* rb = m_owner->GetComponent<Rigidbody2D>();

	if (m_isInPossessionMode) 
	{
		if(im.IsKeyDown(m_switchKey) && m_switchCouldown <= 0)
		{
			m_switchCouldown = 0.02f;

			m_isInPossessionMode = false;

			Entity* possessedEntity = cs->FindByTag("POSSESSED");

			Vector2f targetPos = possessedEntity->GetComponent<TransformComponent>()->GetPos() + Vector2f{ 0, -40 };
			transform->SetPos(targetPos);

			possessedEntity->GetComponent<PossessionLogic>()->SetPossessed(false);
			possessedEntity->GetComponent<TagComponent>()->RemoveTag("POSSESSED");

			for(Collider* c : m_owner->GetAllComponents<Collider>())
			{
				c->SetVisible(true);
				c->SetActive(true);
			}
		}
	}
	else
	{
		Vector2f delta = im.GetMouseDelta();
		float maxDelta = 500.f * _dt;

		if (delta.Length() > maxDelta)
		{
			delta = delta.Normalize() * maxDelta;
		}

		if (delta.Length() > 0)
		{
			float angleRad = std::atan2(delta.GetY(), delta.GetX()) - 1.571f;
			float angleDeg = angleRad * 180.f / 3.14159265f;

			Vector2f localOffset{ 0, 15 };

			float cosA = std::cos(angleRad);
			float sinA = std::sin(angleRad);

			float rotatedOffsetX = localOffset.GetX() * cosA - localOffset.GetY() * sinA;
			float rotatedOffsetY = localOffset.GetX() * sinA + localOffset.GetY() * cosA;

			for (Collider* c : m_owner->GetAllComponents<Collider>())
			{
				if (c->IsTrigger())
					continue;

				c->SetOffset(rotatedOffsetX, rotatedOffsetY);
			}

			transform->SetRotationCenter({ 32, 32 });
			transform->SetRotation(angleDeg);
		}

		rb->SetVelocity(delta / _dt);
	}
}

void SpiritLogic::OnCollisionStay(Collider* _self, Collider* _other)
{
	InputManager& im = InputManager::Get();
	PossessionLogic* pl = _other->GetOwner()->GetComponent<PossessionLogic>();

	if (pl == nullptr)
		return;

	if (_self->IsTrigger() && pl->IsPossessed() == false)
	{
		if (im.IsKeyDown(m_switchKey) && m_switchCouldown <= 0)
		{
			m_switchCouldown = 0.02f;

			_other->GetOwner()->GetComponent<TagComponent>()->AddTag("POSSESSED");
			pl->SetPossessed(true);
			m_isInPossessionMode = true;

			for (Collider* c : m_owner->GetAllComponents<Collider>())
			{
				c->SetVisible(false);
				c->SetActive(false);
			}
		}
	}
}
