#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Collidable.h"
#include "Lib2D/Vector2f.h"

class Vector2f;
typedef enum Key;

class PlayerMovement : public Component, public Updatable, public Collidable
{
	float m_speed;
	Vector2f m_direction;
	Key m_moveUpKey;
	Key m_moveDownKey;

public:
	PlayerMovement(Key _moveUpKey, Key _moveDownKey);
	void Update(float _dt) override;
	void OnCollisionStay(Collider* _self, Collider* _other) override;
};

