#pragma once

class ButtonComponent;

class Hoverable
{
public:
    virtual ~Hoverable() = default;
    virtual void OnHoverEnter(ButtonComponent* _button) {}
    virtual void OnHoverExit(ButtonComponent* _button) {}
};
