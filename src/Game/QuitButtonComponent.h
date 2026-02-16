#pragma once
#include "Component.h"
#include "Clickable.h"

class QuitButtonComponent : public Component, public Clickable
{
public:
	void OnClick(ButtonComponent* _button) override;
};

