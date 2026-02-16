#include "PlayerMovement.h"
#include "Lib2D/InputManager.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "Rigidbody2D.h"
#include "Collider.h"
#include "Entity.h"
#include "MainScene.h"
#include "SceneManager.h"

PlayerMovement::PlayerMovement(Key _moveLeftKey, Key _moveRightKey, Key _moveJumpKey)
{
	m_moveLeftKey = _moveLeftKey;
	m_moveRightKey = _moveRightKey;
	m_moveJumpKey = _moveJumpKey;
	m_speed = 1.2f;
	m_onGround = false;
}

void PlayerMovement::Update(float _dt)
{
	MainScene* cs = static_cast<MainScene*>(SceneManager::GetInstance().GetCurrentScene());

	if (cs->GetMode())
		return;

	InputManager& im = InputManager::Get();
	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();

	float dx = 0;
	float dy = 0;

	if (im.IsKeyHeld(m_moveLeftKey))
	{
		m_direction = { -1, 0 };
		dx += _dt * m_direction.GetX() * m_speed * 500;
	}

	if (im.IsKeyHeld(m_moveRightKey))
	{
		m_direction = { 1, 0 };
		dx += _dt * m_direction.GetX() * m_speed * 500;
	}

	if (im.IsKeyDown(m_moveJumpKey) && m_onGround)
	{
 		m_owner->GetComponent<Rigidbody2D>()->AddImpulse({ 0,-750 });
	}

	transform->Translate(dx, dy);
}

void PlayerMovement::OnCollisionStay(Collider* _self, Collider* _other)
{
	if (_self->GetTop() > _self->GetOwner()->GetComponent<TransformComponent>()->GetPos().GetY()) {
		TagComponent* otherEntityTag = _other->GetOwner()->GetComponent<TagComponent>();
		if (otherEntityTag && otherEntityTag->Is("Ground"))
			m_onGround = true;
	}
}

void PlayerMovement::OnCollisionExit(Collider* _self, Collider* _other)
{
	if (_self->GetTop() > _self->GetOwner()->GetComponent<TransformComponent>()->GetPos().GetY()) {
		TagComponent* otherEntityTag = _other->GetOwner()->GetComponent<TagComponent>();
		if (otherEntityTag && otherEntityTag->Is("Ground"))
			m_onGround = false;
	}
}