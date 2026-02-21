#include "PlayerMovement.h"
#include "Lib2D/InputManager.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "Rigidbody2D.h"
#include "PossessionLogic.h"
#include "SpriteRenderer.h"
#include "Collider.h"
#include "Entity.h"
#include "MainScene.h"
#include "SceneManager.h"
#include "BoxCollider.h"

PlayerMovement::PlayerMovement(Key _moveLeftKey, Key _moveRightKey, Key _moveJumpKey)
{
	m_moveLeftKey = _moveLeftKey;
	m_moveRightKey = _moveRightKey;
	m_moveJumpKey = _moveJumpKey;
	m_speed = 0.6f;
	m_onGround = false;
}

void PlayerMovement::SetAnimation(PlayerAnimState newState)
{
	if (m_animState == newState)
		return;

    m_previousAnimState = m_animState;
	m_animState = newState;
	m_animTimer = 0.f;
	m_currentFrame = 0;
	m_isAnimationFinished = false;

    switch (newState)
    {
    case PlayerAnimState::Idle:                 m_frameDuration = 0.3f; break;
    case PlayerAnimState::Walk:                 m_frameDuration = 0.1f; break;
    case PlayerAnimState::TakeOff:              m_frameDuration = 0.1f; break;
    case PlayerAnimState::Jump:                 m_frameDuration = 0.2f; break;
    case PlayerAnimState::Fall:                 m_frameDuration = 0.2f; break;
    case PlayerAnimState::Land:                 m_frameDuration = 0.1f; break;
    case PlayerAnimState::EnterPossession:      m_frameDuration = 0.2f; break;
    case PlayerAnimState::ExitPossession:       m_frameDuration = 0.2f; break;
    case PlayerAnimState::Despawn:              m_frameDuration = 0.1f; break;
    case PlayerAnimState::Respawn:              m_frameDuration = 0.1f; break;
    case PlayerAnimState::Death:                m_frameDuration = 0.1f; break;
    default:                                    m_frameDuration = 0.1f; break;
    }
}

void PlayerMovement::Update(float _dt)
{
    if (m_isAnimationFinished == false &&
        (m_animState == PlayerAnimState::EnterPossession ||
            m_animState == PlayerAnimState::ExitPossession ||
            m_animState == PlayerAnimState::TakeOff ||
            m_animState == PlayerAnimState::Despawn ||
            m_animState == PlayerAnimState::Respawn ||
            m_animState == PlayerAnimState::Death))
    {
        UpdateAnimation(_dt);
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

    if (canMove && m_wasPossessed == false && m_animState != PlayerAnimState::Respawn)
    {
        SetAnimation(PlayerAnimState::EnterPossession);
    }
    else if (canMove == false && m_wasPossessed)
    {
        SetAnimation(PlayerAnimState::ExitPossession);
    }

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

    if (im.IsKeyHeld(Key::KEY_r))
        SetAnimation(PlayerAnimState::Respawn);

	rb->SetVelocity(velocity);

    
    if (m_isAnimationFinished == false &&
        (m_animState == PlayerAnimState::EnterPossession ||
            m_animState == PlayerAnimState::ExitPossession ||
            m_animState == PlayerAnimState::TakeOff ||
            m_animState == PlayerAnimState::Despawn ||
            m_animState == PlayerAnimState::Respawn ||
            m_animState == PlayerAnimState::Death))
    {
        return;
    }
    else if (m_animState == PlayerAnimState::ExitPossession)
    {
        return;
    }
    else if (canMove && im.IsKeyDown(m_moveJumpKey) && m_onGround)
    {
        SetAnimation(PlayerAnimState::TakeOff);
    }
    else if (m_onGround == false)
    {
        if (velocity.GetY() < 0)
        {
            SetAnimation(PlayerAnimState::Jump);
        }
        else
        {
            SetAnimation(PlayerAnimState::Fall);
        }
    }
    else if(m_animState == PlayerAnimState::Fall)
    {
        SetAnimation(PlayerAnimState::Land);
    }
    else if (std::abs(velocity.GetX()) > 0.5f)
    {
        SetAnimation(PlayerAnimState::Walk);
    }
    else if(m_animState != PlayerAnimState::ExitPossession)
    {
        SetAnimation(PlayerAnimState::Idle);
    }

    UpdateAnimation(_dt);
}


void PlayerMovement::UpdateAnimation(float _dt)
{
    m_animTimer += _dt;

    if (m_animTimer < m_frameDuration)
        return;

    m_animTimer = 0.f;
    m_currentFrame++;

    SpriteRenderer* sr = m_owner->GetComponent<SpriteRenderer>();

    switch (m_animState)
    {
    case PlayerAnimState::Idle:
    {
        if (m_currentFrame >= 6)
            m_currentFrame = 0;

        int x = m_currentFrame % 2;
        int y = 0;

        if (m_currentFrame >= 4)
            y = (m_currentFrame - 2) / 2;

        sr->SetFrame(32, 32, x * 32, y * 32);
        break;
    }

    case PlayerAnimState::Walk:
    {
        if (m_currentFrame >= 8)
            m_currentFrame = 0;

        sr->SetFrame(32, 32, m_currentFrame * 32, 3 * 32);
        break;
    }

    case PlayerAnimState::EnterPossession:
    {
        if (m_currentFrame >= 4)
        {
            m_currentFrame = 3;
            m_isAnimationFinished = true;
        }

        sr->SetFrame(32, 32, (3 - m_currentFrame) * 32, 4 * 32);
        break;
    }

    case PlayerAnimState::ExitPossession:
    {
        if (m_currentFrame >= 4)
        {
            m_currentFrame = 3;
            m_isAnimationFinished = true;
        }

        sr->SetFrame(32, 32, m_currentFrame * 32, 4 * 32);
        break;
    }

    case PlayerAnimState::TakeOff:
    {
        if (m_currentFrame >= 2)
        {
            m_owner->GetComponent<Rigidbody2D>()->SetVelocity({ 0, -600 });
            m_currentFrame = 1;
            m_isAnimationFinished = true;
        }

        sr->SetFrame(32, 32, m_currentFrame * 32, 5 * 32);
        break;
    }

    case PlayerAnimState::Jump:
    {
        if (m_currentFrame >= 2)
            m_currentFrame = 0;

        int frame = 2 + m_currentFrame;

        sr->SetFrame(32, 32, frame * 32, 5 * 32);
        break;
    }

    case PlayerAnimState::Fall:
    {
        if (m_currentFrame >= 3)
            m_currentFrame = 2;

        int frame = 3 + m_currentFrame; 

        sr->SetFrame(32, 32, frame * 32, 5 * 32);
        break;
    }

    case PlayerAnimState::Land:
    {
        m_owner->GetComponent<Rigidbody2D>()->SetVelocity({ 0, 0 });

        if (m_currentFrame >= 2)
        {
            m_currentFrame = 1;
            m_isAnimationFinished = true;
        }

        int frame = 6 + m_currentFrame; 

        sr->SetFrame(32, 32, frame * 32, 5 * 32);
        break;
    }

    case PlayerAnimState::Despawn:
    {
        if (m_currentFrame >= 6)
        {
            m_currentFrame = 5;
            m_isAnimationFinished = true;
        }

        sr->SetFrame(32, 32, m_currentFrame * 32, 6 * 32);
        break;
    }

    case PlayerAnimState::Respawn:
    {
        if (m_currentFrame >= 6)
        {
            m_currentFrame = 5;
            m_isAnimationFinished = true;
        }

        sr->SetFrame(32, 32, (5 - m_currentFrame) * 32, 6 * 32);
        break;
    }

    case PlayerAnimState::Death:
    {
        if (m_currentFrame >= 8)
            m_currentFrame = 7;

        sr->SetFrame(32, 32, m_currentFrame * 32, 7 * 32);
        break;
    }
    }
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