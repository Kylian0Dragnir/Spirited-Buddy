#include "TextComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

TextComponent::TextComponent(std::string _fontPath, int _size)
{
    m_text.Init(_fontPath, _size);
    m_isVisible = true;
}

void TextComponent::SetText(const std::string& _txt)
{
    m_text.SetText(_txt);
}

void TextComponent::SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    m_text.SetDrawColor(r, g, b, a);
}

void TextComponent::Draw(Window* window)
{
    if (m_isVisible == false)
        return;

    TransformComponent* transform = m_owner->GetComponent<TransformComponent>();

    m_text.SetFlip(transform->GetFlip());
    m_text.SetRotation(transform->GetAngle());
    m_text.SetRotationCenter(transform->GetRotationCenter());

    m_text.SetPos(transform->GetPos() + m_offset);
    m_text.Draw(window);
}
