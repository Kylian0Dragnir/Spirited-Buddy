#pragma once
#include "Component.h"
#include "Collidable.h"
#include "Lib2D/Vector2f.h"

class Vector2f;
typedef enum Key;

class CollectibleLogic : public Component, public Collidable
{

public:
	void OnCollisionEnter(Collider* _self, Collider* _other) override;
};

