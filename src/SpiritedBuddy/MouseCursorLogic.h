#pragma once
#include "Component.h"
#include "Updatable.h"

class MouseCursorLogic : public Component, public Updatable
{
public:
	void Update(float _dt) override;
};

