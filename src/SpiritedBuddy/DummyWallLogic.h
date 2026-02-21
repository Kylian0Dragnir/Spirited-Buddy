#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Collidable.h"

class DummyWallLogic : public Component, public Updatable, public Collidable
{
	bool m_playerCollide = false;
	int m_currentOpacity = 255;

public:
	void Update(float _dt) override;
	void OnCollisionEnter(Collider* _self, Collider* _other) override;
};

