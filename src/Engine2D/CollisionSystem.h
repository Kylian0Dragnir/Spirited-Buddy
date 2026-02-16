#pragma once
#include <vector>

class Entity;
class Collider;

struct CollisionInfo
{
    Collider* a;
    Collider* b;
};

class CollisionSystem
{
private:
    std::vector<CollisionInfo> m_previousCollisions;

public:
	void Update(const std::vector<Entity*>& entities);
};

