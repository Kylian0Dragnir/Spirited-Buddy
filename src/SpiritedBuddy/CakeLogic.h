#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Collidable.h"

class CakeLogic : public Component, public Updatable, public Collidable
{
	float m_timer = 0.f;

public:
	void Update(float _dt) override;
	void OnCollisionStay(Collider* _self, Collider* _other) override;
};

