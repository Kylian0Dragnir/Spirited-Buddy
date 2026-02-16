#include "PlayerMovement.h"
#include "TransformComponent.h"
#include "Lib2D/InputManager.h"
#include "Entity.h"
#include "Collider.h"
#include "TagComponent.h"

PlayerMovement::PlayerMovement(Key _moveUpKey, Key _moveDownKey)
{
	m_moveUpKey = _moveUpKey;
	m_moveDownKey = _moveDownKey;
	m_direction = { 0, 0 };
	m_speed = 1.2f;
}

void PlayerMovement::Update(float _dt)
{
	InputManager& im = InputManager::Get();
	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();

	float dx = 0;
	float dy = 0;

	if (im.IsKeyHeld(m_moveUpKey))
	{
		m_direction = { 0, -1 };
		dy += _dt * m_direction.GetY() * m_speed * 500;
	}

	if (im.IsKeyHeld(m_moveDownKey))
	{
		m_direction = { 0, 1 };
		dy += _dt * m_direction.GetY() * m_speed * 500;
	}

	transform->Translate(dx, dy);
}

void PlayerMovement::OnCollisionStay(Collider* _self, Collider* _other)
{
	Entity* otherEntity = _other->GetOwner();

	TagComponent* otherEntityTag = otherEntity->GetComponent<TagComponent>();

	if (otherEntityTag)
	{
		if (otherEntityTag->Is("WALL1"))
		{
			TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
			transform->Translate(0, 7);
		}

		else if (otherEntityTag->Is("WALL2"))
		{
			TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
			transform->Translate(0, -7);
		}
	}
}
