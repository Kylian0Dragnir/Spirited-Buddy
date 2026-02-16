#pragma once
#include "Component.h"
#include "Lib2D/Drawable.h"
#include "Lib2D/Text.h"

class TextComponent : public Component, public Drawable
{
private:
    Text m_text;

public:
    TextComponent(std::string _fontPath, int _size);

    void SetText(const std::string& _txt);
    void SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    void Draw(Window* window) override;
};