#include "ButtonComponent.h"
#include "Entity.h"
#include "Collider.h"
#include "InputManager.h"

#include "Hoverable.h"
#include "Pressable.h"
#include "Clickable.h"

ButtonComponent::ButtonComponent()
{
    m_isHovered = false;
    m_wasHovered = false;

    m_isPressed = false;
    m_wasPressed = false;
}

void ButtonComponent::Update(float)
{
    m_wasHovered = m_isHovered;
    m_wasPressed = m_isPressed;

    m_isHovered = IsMouseOver();
    m_isPressed = m_isHovered && InputManager::Get().IsMouseHeld(MouseButton::LEFT);

    if (!m_wasHovered && m_isHovered)
    {
        for (Hoverable* h : m_owner->GetAllComponents<Hoverable>())
            h->OnHoverEnter(this);
    }
    else if (m_wasHovered && !m_isHovered)
    {
        for (Hoverable* h : m_owner->GetAllComponents<Hoverable>())
            h->OnHoverExit(this);
    }

    if (!m_wasPressed && m_isPressed)
    {
        for (Pressable* p : m_owner->GetAllComponents<Pressable>())
            p->OnPressed(this);
    }
    else if (m_wasPressed && m_isPressed == false)
    {
        for (Pressable* p : m_owner->GetAllComponents<Pressable>())
            p->OnReleased(this);

        if (m_isHovered)
        {
            for (Clickable* c : m_owner->GetAllComponents<Clickable>())
                c->OnClick(this);
        }
    }
}

bool ButtonComponent::IsMouseOver() const
{
    Collider* collider = m_owner->GetComponent<Collider>();

    if (!collider) 
        return false;

    Vector2f mouse = InputManager::Get().GetMousePosition();

    return mouse.GetX() >= collider->GetLeft() &&
        mouse.GetX() <= collider->GetRight() &&
        mouse.GetY() >= collider->GetTop() &&
        mouse.GetY() <= collider->GetBottom();
}
