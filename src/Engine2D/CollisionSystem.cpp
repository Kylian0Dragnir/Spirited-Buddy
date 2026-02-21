#include "CollisionSystem.h"
#include "Entity.h"
#include "Collider.h"
#include "Collidable.h"
#include "SceneManager.h"
#include "AScene.h"

CollisionSystem& CollisionSystem::GetInstance()
{
    static CollisionSystem Instance;
    return Instance;
}

bool SamePair(const CollisionInfo& c1, Collider* a, Collider* b)
{
    return (c1.a == a && c1.b == b) || (c1.a == b && c1.b == a);
}

bool WasColliding(const std::vector<CollisionInfo>& list, Collider* a, Collider* b)
{
    for (const CollisionInfo& c : list)
    {
        if (SamePair(c, a, b))
            return true;
    }

    return false;
}

void CollisionSystem::Update(const std::vector<Entity*>& entities)
{
    std::vector<Collider*> colliders;
    std::vector<CollisionInfo> currentCollisions;

    for (Entity* e : entities)
    {
        auto cols = e->GetAllComponents<Collider>();
        colliders.insert(colliders.end(), cols.begin(), cols.end());
    }

    for (int i = 0; i < colliders.size(); ++i)
    {
        for (int j = i + 1; j < colliders.size(); ++j)
        {
            Collider* a = colliders[i];
            Collider* b = colliders[j];

            if (a->GetOwner() == b->GetOwner())
                continue;

            if (a->CanCollide(b) == false)
                continue;

            if (a->IsColliding(b) == false)
                continue;

            currentCollisions.push_back({ a, b });

            bool wasColliding = WasColliding(m_previousCollisions, a, b);

            auto aListeners = a->GetOwner()->GetAllComponents<Collidable>();
            auto bListeners = b->GetOwner()->GetAllComponents<Collidable>();

            if (wasColliding == false)
            {
                for (Collidable* c : aListeners)
                    c->OnCollisionEnter(a, b);

                for (Collidable* c : bListeners)
                    c->OnCollisionEnter(b, a);
            }

            for (Collidable* c : aListeners)
                c->OnCollisionStay(a, b);

            for (Collidable* c : bListeners)
                c->OnCollisionStay(b, a);
        }
    }

    for (const CollisionInfo& oldCol : m_previousCollisions)
    {
        if (WasColliding(currentCollisions, oldCol.a, oldCol.b) == false)
        {
            auto aListeners = oldCol.a->GetOwner()->GetAllComponents<Collidable>();
            auto bListeners = oldCol.b->GetOwner()->GetAllComponents<Collidable>();

            for (Collidable* c : aListeners)
                c->OnCollisionExit(oldCol.a, oldCol.b);

            for (Collidable* c : bListeners)
                c->OnCollisionExit(oldCol.b, oldCol.a);
        }
    }

    m_previousCollisions = currentCollisions;
}

void CollisionSystem::Clear(Entity* entity)
{
    std::vector<Collider*> colliders = entity->GetAllComponents<Collider>();

    m_previousCollisions.erase(
        std::remove_if(
            m_previousCollisions.begin(),
            m_previousCollisions.end(),
            [&colliders](const CollisionInfo& info)
            {
                for (Collider* col : colliders)
                {
                    if (info.a == col || info.b == col)
                        return true;
                }
                return false;
            }
        ),
        m_previousCollisions.end()
    );
}

