#include "BoxCollider.h"
#include "Window.h"
#include "CircleCollider.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Brush.h"

bool BoxCollider::IsColliding(Collider* other)
{
    if (m_isActived == false || other->IsActived() == false)
        return false;

    if (other->GetType() == ColliderType::Rectangle)
    {
        BoxCollider* r = (BoxCollider*)other;

        return !(GetRight() < r->GetLeft() ||
            GetLeft() > r->GetRight() ||
            GetBottom() < r->GetTop() ||
            GetTop() > r->GetBottom());
    }
    else // Circle
    {
        CircleCollider* c = (CircleCollider*)other;

        Vector2f pos = c->GetOwner()->GetComponent<TransformComponent>()->GetPos();
        float radius = c->GetRadius();

        // clamp du point du cercle dans le rectangle
        float closestX = std::max(GetLeft(), std::min(pos.GetX(), GetRight()));
        float closestY = std::max(GetTop(), std::min(pos.GetY(), GetBottom()));

        float dx = closestX - pos.GetX();
        float dy = closestY - pos.GetY();

        return dx * dx + dy * dy <= radius * radius;
    }
}

void BoxCollider::Draw(Window* _window)
{
    if (m_isVisible == false)
        return;

    Vector2f pos = m_owner->GetComponent<TransformComponent>()->GetPos();

    Brush::DrawRect(_window, pos.GetX() + m_offsetX - m_width * 0.5f, pos.GetY() + m_offsetY - m_height * 0.5f, m_width, m_height);
}

void BoxCollider::SetBox(float _width, float _height)
{
    m_width = _width;
    m_height = _height;
}

float BoxCollider::GetLeft()
{
    Vector2f pos = m_owner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetX() + m_offsetX - m_width * 0.5f;
}

float BoxCollider::GetRight()
{
    Vector2f pos = m_owner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetX() + m_offsetX + m_width * 0.5f;
}

float BoxCollider::GetTop()
{
    Vector2f pos = m_owner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetY() + m_offsetY - m_height * 0.5f;
}

float BoxCollider::GetBottom()
{
    Vector2f pos = m_owner->GetComponent<TransformComponent>()->GetPos();
    return pos.GetY() + m_offsetY + m_height * 0.5f;
}
