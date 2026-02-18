#pragma once
#include "Component.h"
#include "Updatable.h"
#include "Collidable.h"
#include <string>

enum class PortalState
{
	Hidden,       
	Appearing,     
	Idle,          
	Disappearing  
};

class PortalLogic : public Component, public Updatable, public Collidable
{
	int m_frameX = 512;
	int m_frameY = 0;

	float m_timer = 0.f;

	std::string m_nextSceneID;

	PortalState m_state = PortalState::Hidden;

	void HandleAppear(float _dt);
	void HandleDisappear(float _dt);

public:
	PortalLogic(const std::string& _nextSceneID);
	void Update(float dt) override;
	void OnCollisionStay(Collider* _self, Collider* _other) override;

	void Appear();
};

