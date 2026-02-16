#pragma once
#include "Component.h"
#include "Clickable.h"

class StartMultiButtonComponent : public Component, public Clickable
{
public:
	void OnClick(ButtonComponent* _button) override;
};

