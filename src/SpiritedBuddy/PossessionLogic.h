#pragma once
#include "Component.h"

class PossessionLogic : public Component
{
	bool m_isPossessed;

public:
	bool IsPossessed() { return m_isPossessed; }
	void SetPossessed(bool _state) { m_isPossessed = _state; }
};

