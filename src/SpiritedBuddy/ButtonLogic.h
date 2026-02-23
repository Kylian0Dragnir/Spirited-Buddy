#pragma once
#include <functional>
#include "Component.h"
#include "Collidable.h"

enum class ButtonMode
{
	Hold,
	Toggle
};

class ButtonLogic : public Component, public Collidable
{
private:
	bool m_isPressed;
	int m_PhysicObjectsOn;

	ButtonMode m_mode;

	std::function<void()> m_onActivate;
	std::function<void()> m_onDeactivate;

public:
	ButtonLogic(ButtonMode mode = ButtonMode::Hold);

	void SetOnActivate(const std::function<void()>& func) { m_onActivate = func; }
	void SetOnDeactivate(const std::function<void()>& func) { m_onDeactivate = func; }

	bool IsPressed() { return m_isPressed; }

	void OnCollisionEnter(Collider* self, Collider* other) override;
	void OnCollisionExit(Collider* self, Collider* other) override;

private:
	void Activate();
	void Deactivate();
};

