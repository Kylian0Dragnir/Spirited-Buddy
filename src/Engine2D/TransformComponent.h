#pragma once
#include "Lib2D/Transformable.h"
#include "Component.h"

class TransformComponent : public Component, public Transformable
{
public:
	TransformComponent() : Transformable({0, 0}) {}
};

