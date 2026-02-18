#include "PlayerMovement.h"
#include "Lib2D/InputManager.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "Rigidbody2D.h"
#include "PossessionLogic.h"
#include "Collider.h"
#include "Entity.h"
#include "MainScene.h"
#include "SceneManager.h"

PlayerMovement::PlayerMovement(Key _moveLeftKey, Key _moveRightKey, Key _moveJumpKey)
{
	m_moveLeftKey = _moveLeftKey;
	m_moveRightKey = _moveRightKey;
	m_moveJumpKey = _moveJumpKey;
	m_speed = 0.6f;
	m_onGround = false;
}

void PlayerMovement::Update(float _dt)
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

	if (canMove && im.IsKeyDown(m_moveJumpKey) && m_onGround)
	{
		velocity.SetY(-750);
	}

	rb->SetVelocity(velocity);
}

void PlayerMovement::OnCollisionStay(Collider* _self, Collider* _other)
{
	if (_self->GetTop() > m_owner->GetComponent<TransformComponent>()->GetPos().GetY()) {
		TagComponent* otherEntityTag = _other->GetOwner()->GetComponent<TagComponent>();
		if (otherEntityTag && otherEntityTag->Is("Ground"))
			m_onGround = true;
	}
}

void PlayerMovement::OnCollisionExit(Collider* _self, Collider* _other)
{
	if (_self->GetTop() > m_owner->GetComponent<TransformComponent>()->GetPos().GetY()) {
		TagComponent* otherEntityTag = _other->GetOwner()->GetComponent<TagComponent>();
		if (otherEntityTag && otherEntityTag->Is("Ground"))
			m_onGround = false;
	}
}