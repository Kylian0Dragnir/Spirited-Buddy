#include "PhysicObjectMovement.h"
#include "Lib2D/InputManager.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "Rigidbody2D.h"
#include "Collider.h"
#include "Entity.h"
#include "MainScene.h"
#include "SceneManager.h"

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

	float dx = 0;
	float dy = 0;

	Vector2f velocity = rb->GetVelocity();

	if (im.IsKeyHeld(m_moveLeftKey))
	{
		velocity.SetX(-m_speed * 500);
		transform->SetFlip(Flip::FLIP_NONE);
	}
	else if (im.IsKeyHeld(m_moveRightKey))
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
	}

	rb->SetVelocity(velocity);
}