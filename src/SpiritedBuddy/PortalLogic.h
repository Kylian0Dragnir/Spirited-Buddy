#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Collidable.h"

class PortalLogic : public Component, public Updatable, public Collidable
{
	int m_frameX = 0;
	int m_frameY = 0;

	float m_timer = 0.f;

	bool m_teleportRequested;

public:
	void Update(float dt) override;
	void OnCollisionStay(Collider* _self, Collider* _other) override;
};

