#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Collidable.h"
#include <string>

enum class DummyPortalState
{
	Hidden,
	Appearing,
	Idle,
	Disappearing
};

class DummyPortalLogic : public Component, public Updatable, public Collidable
{
	int m_frameX = 512;
	int m_frameY = 0;

	float m_timer = 0.f;

	DummyPortalState m_state = DummyPortalState::Appearing;

	Entity* m_player = nullptr;

	void HandleAppear(float _dt);
	void HandleDisappear(float _dt);

public:
	DummyPortalLogic();
	void Update(float dt) override;
	void OnCollisionStay(Collider* _self, Collider* _other) override;

	void Appear();
};

