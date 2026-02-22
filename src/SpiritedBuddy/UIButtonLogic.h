#pragma once
#include <functional>
#include "Component.h"
#include "Updatable.h"
#include "Collidable.h"

class UIButtonLogic : public Component, public Updatable, public Collidable
{
private:
	bool m_isHovered;
	std::function<void()> m_onClick;

public:

	void SetOnClick(const std::function<void()>& func) { m_onClick = func; }

	void Update(float _dt) override;

	void OnCollisionStay(Collider* self, Collider* other) override;
	void OnCollisionExit(Collider* self, Collider* other) override;

private:
	void Activate();
};

