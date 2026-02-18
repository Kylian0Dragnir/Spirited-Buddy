#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Lib2D/Vector2f.h"

typedef enum Key;

class PhysicObjectMovement : public Component, public Updatable
{
	float m_speed;
	Vector2f m_direction;
	Key m_moveLeftKey;
	Key m_moveRightKey;

public:
	PhysicObjectMovement(Key m_moveLeftKey, Key m_moveRightKey);
	void Update(float _dt) override;
};

