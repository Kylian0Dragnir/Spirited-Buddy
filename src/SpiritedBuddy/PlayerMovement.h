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

	bool m_isPlayingWalking;
	bool m_wasPlayingWalking;

	bool m_onGround;
	bool m_wasOnGround;
	bool m_wasPossessed;
	bool m_jumpRequested;

public:
	PlayerMovement(Key m_moveLeftKey, Key m_moveRightKey, Key m_moveJumpKey);
	void Update(float _dt) override;
	void OnCollisionEnter(Collider* _self, Collider* _other) override;
	void OnCollisionStay(Collider* _self, Collider* _other) override;
	void OnCollisionExit(Collider* _self, Collider* _other) override;

	void Jump() { m_jumpRequested = true; }
};

