#include "MouseCursorLogic.h"
#include "Lib2D/InputManager.h"
#include "Rigidbody2D.h"
#include "Entity.h"

void MouseCursorLogic::Update(float _dt)
{
	m_owner->GetComponent<Rigidbody2D>()->SetVelocity(InputManager::Get().GetMouseDelta() / _dt);
}
