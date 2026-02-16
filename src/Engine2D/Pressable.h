#pragma once

class ButtonComponent;

class Pressable
{
public:
    virtual ~Pressable() = default;
    virtual void OnPressed(ButtonComponent* _button) {}
    virtual void OnReleased(ButtonComponent* _button) {}
};
