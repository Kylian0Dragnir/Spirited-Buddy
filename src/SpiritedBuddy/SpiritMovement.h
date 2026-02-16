#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Collidable.h"
#include "Lib2D/Vector2f.h"

class Vector2f;
typedef enum Key;

class SpiritMovement : public Component, public Updatable, public Collidable
{
	float m_speed;
	Vector2f m_direction;
	Vector2f m_mousePos;
	Key m_switchKey;

	Entity* m_player;

public:
	SpiritMovement(Key _switchKey);
	void Update(float _dt) override;
	void OnCollisionStay(Collider* _self, Collider* _other) override;
};

