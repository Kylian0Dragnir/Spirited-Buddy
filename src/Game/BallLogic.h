#pragma once
#include "Component.h"
#include "Collidable.h"

class BallLogic : public Component, public Collidable
{
public:
    void ServeRandom(float speed);
    void Reset();

    void OnCollisionEnter(Collider* _self, Collider* _other) override;
};


