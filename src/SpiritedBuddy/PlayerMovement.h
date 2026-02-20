#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Collidable.h"
#include "Lib2D/Vector2f.h"

class Vector2f;
typedef enum Key;

enum class PlayerAnimState
{
	Idle,
	Walk,
	TakeOff,
	Jump,
	Fall,
	Land,
	EnterPossession,
	ExitPossession,
	Despawn,
	Respawn,
	Death
};

class PlayerMovement : public Component, public Updatable, public Collidable
{
	float m_speed;
	Vector2f m_direction;
	Key m_moveLeftKey;
	Key m_moveRightKey;
	Key m_moveJumpKey;

	bool m_onGround;
	bool m_wasPossessed;

	PlayerAnimState m_animState;
	PlayerAnimState m_previousAnimState;

	float m_animTimer = 0.f;
	float m_frameDuration = 0.1f;

	int m_currentFrame = 0;
	bool m_isAnimationFinished = false;

public:
	PlayerMovement(Key m_moveLeftKey, Key m_moveRightKey, Key m_moveJumpKey);
	void SetAnimation(PlayerAnimState newState);
	void Update(float _dt) override;
	void UpdateAnimation(float _dt);
	void OnCollisionStay(Collider* _self, Collider* _other) override;
	void OnCollisionExit(Collider* _self, Collider* _other) override;
};

