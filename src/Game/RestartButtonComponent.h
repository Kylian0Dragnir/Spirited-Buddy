#pragma once
#include "Component.h"
#include "Clickable.h"

class RestartButtonComponent : public Component, public Clickable
{
public:
	void OnClick(ButtonComponent* _button) override;
};

