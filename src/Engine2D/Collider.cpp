#include "Collider.h"

Collider::Collider(ColliderType type)
{
    m_type = type;
    m_offsetX = 0;
    m_offsetY = 0;

    m_isActived = true;
    m_isVisible = false;
}

void Collider::SetOffset(float _ox, float _oy)
{
    m_offsetX = _ox;
    m_offsetY = _oy;
}