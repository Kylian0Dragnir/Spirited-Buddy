#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Collidable.h"
#include "Lib2D/Vector2f.h"

typedef enum Key;

class PhysicObjectMovement : public Component, public Updatable, public Collidable
{
	float m_speed;
	Vector2f m_direction;
	Key m_moveLeftKey;
	Key m_moveRightKey;

	bool m_onGround;

public:
	PhysicObjectMovement(Key m_moveLeftKey, Key m_moveRightKey);
	void Update(float _dt) override;
	void OnCollisionStay(Collider* _self, Collider* _other) override;
	void OnCollisionExit(Collider* _self, Collider* _other) override;
};

