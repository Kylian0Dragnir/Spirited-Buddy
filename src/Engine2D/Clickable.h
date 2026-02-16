#pragma once

class ButtonComponent;

class Clickable
{
public:
    virtual ~Clickable() = default;
    virtual void OnClick(ButtonComponent* _button) {}
};
