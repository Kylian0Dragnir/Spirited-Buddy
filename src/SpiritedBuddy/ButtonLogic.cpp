#include "ButtonLogic.h"
#include "TagComponent.h"
#include "Collider.h"
#include "Entity.h"
#include "SpriteRenderer.h"
#include "Lib2D/AudioEngine.h"

ButtonLogic::ButtonLogic(ButtonMode mode)
{
	m_mode = mode;
    m_isPressed = false;
}

void ButtonLogic::OnCollisionEnter(Collider* self, Collider* other)
{
    if (other->IsTrigger())
        return;

    if (self->IsTrigger() == false)
        return;

    m_PhysicObjectsOn++;

    if (m_PhysicObjectsOn == 1)
    {
        if (m_mode == ButtonMode::Hold)
        {
            Activate();
        }
        else if (m_mode == ButtonMode::Toggle)
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
    if (other->IsTrigger())
        return;

    if (self->IsTrigger() == false)
        return;

    m_PhysicObjectsOn--;

    if (m_PhysicObjectsOn < 0)
        m_PhysicObjectsOn = 0;

    if (m_mode == ButtonMode::Hold)
    {
        if (m_PhysicObjectsOn == 0)
        {
            Deactivate();
        }
    }
}

void ButtonLogic::Activate()
{
    if (m_isPressed)
        return;

    AudioEngine::Get().PlaySound("BUTTON_DOWN", false, 50);

    m_owner->GetComponent<SpriteRenderer>()->SetFrame(32,32,32,0);

    m_isPressed = true;

    if (m_onActivate)
        m_onActivate();
}

void ButtonLogic::Deactivate()
{
    if (!m_isPressed)
        return;

    AudioEngine::Get().PlaySound("BUTTON_UP", false, 50);

    m_owner->GetComponent<SpriteRenderer>()->SetFrame(32, 32, 0, 0);

    m_isPressed = false;

    if (m_onDeactivate)
        m_onDeactivate();
}
