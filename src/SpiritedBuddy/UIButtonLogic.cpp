#include "UIButtonLogic.h"
#include "TagComponent.h"
#include "Collider.h"
#include "Lib2D/InputManager.h"
#include "Lib2D/AudioEngine.h"

void UIButtonLogic::Update(float _dt)
{
    if (m_isHovered && m_wasHovered == false)
        AudioEngine::Get().PlaySound("UI_HOVER", false);

    m_wasHovered = m_isHovered;
}

void UIButtonLogic::OnCollisionStay(Collider* self, Collider* other)
{
    m_isHovered = true;

    if(InputManager::Get().IsMouseDown(MouseButton::LEFT))
    {
        AudioEngine::Get().PlaySound("UI_CLICK", false);

        if (m_onClick)
            m_onClick();
    }
}

void UIButtonLogic::OnCollisionExit(Collider* self, Collider* other)
{
    m_isHovered = false;
}
