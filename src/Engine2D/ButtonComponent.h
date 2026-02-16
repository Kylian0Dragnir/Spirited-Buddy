#pragma once
#include "Component.h"
#include "Updatable.h"

class ButtonComponent : public Component, public Updatable
{
public:
    ButtonComponent();
    void Update(float dt) override;

private:
    bool IsMouseOver() const;

    bool m_isHovered;
    bool m_wasHovered;

    bool m_isPressed;
    bool m_wasPressed;
};

