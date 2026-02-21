#pragma once
#include "Component.h"
#include "Updatable.h"

class WorldWrapLogic : public Component, public Updatable
{
	Entity* m_clone;

public:
	WorldWrapLogic();
	void Update(float _dt) override;
	void Generate();
};