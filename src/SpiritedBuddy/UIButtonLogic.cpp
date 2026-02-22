#include "UIButtonLogic.h"
#include "TagComponent.h"
#include "Collider.h"
#include "Lib2D/InputManager.h"

void UIButtonLogic::Update(float _dt)
{
}

void UIButtonLogic::OnCollisionStay(Collider* self, Collider* other)
{
    m_isHovered = true;

    if(InputManager::Get().IsMouseDown(MouseButton::LEFT))
    {
        if (m_onClick)
            m_onClick();
    }
}

void UIButtonLogic::OnCollisionExit(Collider* self, Collider* other)
{
    m_isHovered = false;
}
