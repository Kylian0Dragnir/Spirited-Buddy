#include "ButtonLogic.h"
#include "TagComponent.h"
#include "Collider.h"

ButtonLogic::ButtonLogic(ButtonMode mode)
{
	m_mode = mode;
}

void ButtonLogic::Update(float _dt)
{
	if (m_mode == ButtonMode::Hold)
	{
		if (m_isPlayerOnTop)
			Activate();
	}
}

void ButtonLogic::OnCollisionEnter(Collider* self, Collider* other)
{
    if (self->IsTrigger())
    {
        m_isPlayerOnTop = true;

        if (m_mode == ButtonMode::Toggle)
        {
            if (m_isPressed)
                Deactivate();
            else
                Activate();
        }
    }
}

void ButtonLogic::OnCollisionExit(Collider* self, Collider* other)
{
    if (self->IsTrigger())
    {
        m_isPlayerOnTop = false;

        if (m_mode == ButtonMode::Hold)
        {
            Deactivate();
        }
    }
}

void ButtonLogic::Activate()
{
    if (m_isPressed)
        return;

    m_isPressed = true;

    if (m_onActivate)
        m_onActivate();
}

void ButtonLogic::Deactivate()
{
    if (!m_isPressed)
        return;

    m_isPressed = false;

    if (m_onDeactivate)
        m_onDeactivate();
}
