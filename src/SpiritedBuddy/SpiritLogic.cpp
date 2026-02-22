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

SpiritLogic::SpiritLogic(Key _switchKey, Entity* initialPossessed)
{
	m_switchKey = _switchKey;
	m_speed = 2.2f;

	m_switchCooldown = 0.6f;

	m_possessedEntity = initialPossessed;
}

void SpiritLogic::Update(float _dt)
{
	if (m_switchCooldown > 0)
		m_switchCooldown -= _dt;

	AScene* cs = SceneManager::GetInstance().GetCurrentScene();
	InputManager& im = InputManager::Get();
	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
	Rigidbody2D* rb = m_owner->GetComponent<Rigidbody2D>();

	if (IsPossessing()) 
	{
		if(im.IsKeyDown(m_switchKey) && m_switchCooldown <= 0)
		{
			m_switchCooldown = 0.6f;

			Vector2f targetPos = m_possessedEntity->GetComponent<TransformComponent>()->GetPos() + Vector2f{ 0, -40 };
			transform->SetPos(targetPos);

			m_possessedEntity->GetComponent<PossessionLogic>()->SetPossessed(false);

			m_possessedEntity = nullptr;

			for(Collider* c : m_owner->GetAllComponents<Collider>())
			{
				c->SetVisible(true);
				c->SetActive(true);
			}

			m_owner->GetComponent<SpriteRenderer>()->SetVisible(true);
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

		float targetAngle = 0.f;
		float rotationSpeed = 180.f; // degres/sec

		if (delta.Length() > 0)
		{
			targetAngle = std::atan2(delta.GetY(), delta.GetX()) - 1.571f;
			targetAngle *= 180.f / M_PI;

			rotationSpeed = 360.f;
		}

		float currentAngle = transform->GetAngle();

		float diff = targetAngle - currentAngle;

		while (diff > 180.f) diff -= 360.f;
		while (diff < -180.f) diff += 360.f;

		float maxStep = rotationSpeed * _dt;

		if (std::abs(diff) < maxStep)
			currentAngle = targetAngle;
		else
			transform->SetRotation(currentAngle + (diff > 0 ? maxStep : -maxStep));

		rb->SetVelocity(delta / _dt);



		Collider* ownerCollider = m_owner->GetComponent<Collider>();

		float ownerWidthMiddle = 0;
		float ownerHeightMiddle = 0;

		if (ownerCollider->GetType() == ColliderType::Rectangle)
		{
			ownerWidthMiddle = static_cast<BoxCollider*>(ownerCollider)->GetWidth() / 2;
			ownerHeightMiddle = static_cast<BoxCollider*>(ownerCollider)->GetHeight() / 2;
		}

		if (transform->GetPos().GetX() - ownerWidthMiddle > 1920)
			transform->SetPos({ transform->GetPos().GetX() - 1920, transform->GetPos().GetY() });
		if (transform->GetPos().GetX() + ownerWidthMiddle < 0)
			transform->SetPos({ transform->GetPos().GetX() + 1920, transform->GetPos().GetY() });
		if (transform->GetPos().GetY() - ownerHeightMiddle > 1080)
			transform->SetPos({ transform->GetPos().GetX(), transform->GetPos().GetY() - 1080 });
		if (transform->GetPos().GetY() + ownerHeightMiddle < 0)
			transform->SetPos({ transform->GetPos().GetX(), transform->GetPos().GetY() + 1080 });
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
		if (im.IsKeyDown(m_switchKey) && m_switchCooldown <= 0)
		{
			m_switchCooldown = 0.6f;

			pl->SetPossessed(true);
			m_possessedEntity = _other->GetOwner();

			for (Collider* c : m_owner->GetAllComponents<Collider>())
			{
				c->SetVisible(false);
				c->SetActive(false);
			}

			m_owner->GetComponent<SpriteRenderer>()->SetVisible(false);
		}
	}
}
