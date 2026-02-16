#pragma once
#include "Component.h"
#include "Collidable.h"

class GoalComponent : public Component, public Collidable
{
public:
	void OnCollisionEnter(Collider* _self, Collider* _other) override;
};

