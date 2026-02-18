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
    CollisionSystem() {};

public:
    static CollisionSystem& GetInstance();
	void Update(const std::vector<Entity*>& entities);
    void Clear() { m_previousCollisions.clear(); }
};

