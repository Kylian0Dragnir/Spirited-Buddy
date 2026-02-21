#include "PlayerMovement.h"
#include "Lib2D/InputManager.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "Rigidbody2D.h"
#include "PossessionLogic.h"
#include "SpriteRenderer.h"
#include "Collider.h"
#include "Entity.h"
#include "SceneManager.h"
#include "AnimatorComponent.h"

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
    AnimatorComponent* animator = m_owner->GetComponent<AnimatorComponent>();

    if (animator->IsFinished() == false &&
        (animator->IsPlaying("EnterPossession") ||
            animator->IsPlaying("ExitPossession") ||
            animator->IsPlaying("TakeOff") ||
            animator->IsPlaying("Land") ||
            animator->IsPlaying("Despawn") ||
            animator->IsPlaying("Respawn") ||
            animator->IsPlaying("Death")))
    {
        return;
    }

	InputManager& im = InputManager::Get();
	Rigidbody2D* rb = m_owner->GetComponent<Rigidbody2D>();
	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
	PossessionLogic* pl = m_owner->GetComponent<PossessionLogic>();

	float dx = 0;
	float dy = 0;

	Vector2f velocity = rb->GetVelocity();

	bool canMove = pl->IsPossessed();


    if (m_wasOnGround == false && m_onGround)
    {
        animator->Play("Land");
    }
    else if (canMove && m_wasPossessed == false && animator->IsPlaying("Respawn") == false)
    {
        animator->Play("EnterPossession");
    }
    else if (canMove == false && m_wasPossessed)
    {
        animator->Play("ExitPossession");
    }

    m_wasOnGround = m_onGround;
    m_wasPossessed = canMove;

	if (canMove && im.IsKeyHeld(m_moveLeftKey))
	{
		velocity.SetX(-m_speed * 500);
		transform->SetFlip(Flip::FLIP_HORIZONTAL);
	}
	else if (canMove && im.IsKeyHeld(m_moveRightKey))
	{
		velocity.SetX(m_speed * 500);
		transform->SetFlip(Flip::FLIP_NONE);
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

    if (m_jumpRequested)
    {
        m_jumpRequested = false;
        velocity.SetY(velocity.GetY() - 600);
    }

	rb->SetVelocity(velocity);

    
    if (animator->IsFinished() == false &&
        (animator->IsPlaying("EnterPossession") ||
            animator->IsPlaying("ExitPossession") ||
            animator->IsPlaying("TakeOff") ||
            animator->IsPlaying("Land") ||
            animator->IsPlaying("Despawn") ||
            animator->IsPlaying("Respawn") ||
            animator->IsPlaying("Death")))
    {
        return;
    }
    else if (animator->IsPlaying("ExitPossession"))
    {
        return;
    }
    else if (canMove && im.IsKeyDown(m_moveJumpKey) && m_onGround)
    {
        animator->Play("TakeOff");
    }
    else if (m_onGround == false)
    {
        if (velocity.GetY() < 0)
        {
            animator->Play("Jump");
        }
        else
        {
            animator->Play("Fall");
        }
    }
    else if (std::abs(velocity.GetX()) > 0.5f)
    {
        animator->Play("Walk");
    }
    else
    {
        animator->Play("Idle");
    }
}

void PlayerMovement::OnCollisionStay(Collider* _self, Collider* _other)
{
	if (_self->GetTop() > m_owner->GetComponent<TransformComponent>()->GetPos().GetY()) {
		TagComponent* otherEntityTag = _other->GetOwner()->GetComponent<TagComponent>();
		if (otherEntityTag && (otherEntityTag->Is("Ground") || otherEntityTag->Is("PhysicObject")))
			m_onGround = true;
	}
}

void PlayerMovement::OnCollisionExit(Collider* _self, Collider* _other)
{
	if (_self->GetTop() > m_owner->GetComponent<TransformComponent>()->GetPos().GetY()) {
		TagComponent* otherEntityTag = _other->GetOwner()->GetComponent<TagComponent>();
		if (otherEntityTag && (otherEntityTag->Is("Ground") || otherEntityTag->Is("PhysicObject")))
			m_onGround = false;
	}
}