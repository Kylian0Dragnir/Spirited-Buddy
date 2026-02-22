#pragma once
#include "Component.h"
#include "Lib2D/Drawable.h"
#include "Lib2D/Text.h"
#include "Lib2D/Vector2f.h"

class TextComponent : public Component, public Drawable
{
private:
    Text m_text;
    Vector2f m_offset;

    bool m_isVisible;

public:
    TextComponent(std::string _fontPath, int _size);

    void SetText(const std::string& _txt);
    void SetVisible(bool visible) { m_isVisible = visible; }
    void SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void SetOffset(Vector2f offset) { m_offset = offset; }

    void Draw(Window* window) override;
};