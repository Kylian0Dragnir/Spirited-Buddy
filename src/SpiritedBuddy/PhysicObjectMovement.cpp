#include "PhysicObjectMovement.h"
#include "Lib2D/InputManager.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "Rigidbody2D.h"
#include "PossessionLogic.h"
#include "Collider.h"
#include "Entity.h"
#include "BoxCollider.h"

PhysicObjectMovement::PhysicObjectMovement(Key _moveLeftKey, Key _moveRightKey)
{
	m_moveLeftKey = _moveLeftKey;
	m_moveRightKey = _moveRightKey;
	m_speed = 0.6f;
}
                   
void PhysicObjectMovement::Update(float _dt)
{ 
	InputManager& im = InputManager::Get();
	Rigidbody2D* rb = m_owner->GetComponent<Rigidbody2D>();
	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
	PossessionLogic* pl = m_owner->GetComponent<PossessionLogic>();

	float dx = 0;
	float dy = 0;

	Vector2f velocity = rb->GetVelocity();

	bool canMove = pl->IsPossessed();

	if (canMove && im.IsKeyHeld(m_moveLeftKey))
	{
		velocity.SetX(-m_speed * 500);
		transform->SetFlip(Flip::FLIP_NONE);
	}
	else if (canMove && im.IsKeyHeld(m_moveRightKey))
	{
		velocity.SetX(m_speed * 500);
		transform->SetFlip(Flip::FLIP_HORIZONTAL);
	}
	else
	{
		if (velocity.GetX() > 0)
			velocity.SetX(velocity.GetX() - 7.f);
		else
			velocity.SetX(velocity.GetX() + 7.f);

		if (m_onGround)
			velocity.SetX(0);
	}

	rb->SetVelocity(velocity);


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

void PhysicObjectMovement::OnCollisionStay(Collider* _self, Collider* _other)
{
	TagComponent* otherEntityTag = _other->GetOwner()->GetComponent<TagComponent>();
	if (otherEntityTag && (otherEntityTag->Is("Ground") || otherEntityTag->Is("PhysicObject")))
		m_onGround = true;
}

void PhysicObjectMovement::OnCollisionExit(Collider* _self, Collider* _other)
{
	TagComponent* otherEntityTag = _other->GetOwner()->GetComponent<TagComponent>();
	if (otherEntityTag && (otherEntityTag->Is("Ground") || otherEntityTag->Is("PhysicObject")))
		m_onGround = false;
}