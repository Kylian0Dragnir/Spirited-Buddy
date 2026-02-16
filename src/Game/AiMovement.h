#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Collidable.h"
#include "Lib2D/Vector2f.h"

class Vector2f;
class Entity;

class AiMovement : public Component, public Updatable, public Collidable
{
	float m_speed;
	Vector2f m_direction;
	Entity* m_entityFollow;

public:
	AiMovement();
	void Update(float _dt) override;
	void OnCollisionStay(Collider* _self, Collider* _other) override;
};

