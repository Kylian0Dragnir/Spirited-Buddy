#include "Rigidbody2D.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

Rigidbody2D::Rigidbody2D(float mass, bool useGravity, float restitution)
{
    m_mass = mass;
    m_useGravity = useGravity;
    m_restitution = restitution;
    m_isKinematic = false;

    m_safeMargin = 0.1f;

    m_velocity = { 0, 0 };
    m_acceleration = { 0, 0 };
    m_gravity = { 0, 9.81f };
}

void Rigidbody2D::AddForce(Vector2f force)
{
    m_acceleration = m_acceleration + (force / m_mass);
}

void Rigidbody2D::AddImpulse(Vector2f impulse)
{
    m_velocity = m_velocity + (impulse / m_mass);
}

void Rigidbody2D::SetVelocity(const Vector2f& vel)
{
    m_velocity = vel;
}

Vector2f Rigidbody2D::GetVelocity() const
{
    return m_velocity;
}

void Rigidbody2D::Update(float deltaTime)
{
    if (m_isKinematic)
        return;

    if (m_useGravity)
        m_acceleration = m_acceleration + m_gravity;

    m_velocity = m_velocity + (m_acceleration * deltaTime);

    TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
    if (transform)
    {
        Vector2f newPos = transform->GetPos() + (m_velocity * deltaTime);
        transform->SetPos(newPos);
    }

    m_acceleration = Vector2f(0, 0);
}

void Rigidbody2D::OnCollisionStay(Collider* _self, Collider* _other)
{
    if (_self->IsTrigger() || _other->IsTrigger())
        return;

    Rigidbody2D* otherRb = _other->GetOwner()->GetComponent<Rigidbody2D>();

    TransformComponent* selfTransform = _self->GetOwner()->GetComponent<TransformComponent>();
    TransformComponent* otherTransform = _other->GetOwner()->GetComponent<TransformComponent>();

    Vector2f selfTransformPos = selfTransform->GetPos();
    Vector2f otherTransformPos = otherTransform->GetPos();

    Vector2f selfPos = selfTransformPos + _self->GetOffset();
    Vector2f otherPos = otherTransformPos + _other->GetOffset();

    Vector2f normal;
    float penetrationDepth = 0.0f;

    ColliderType selfType = _self->GetType();
    ColliderType otherType = _other->GetType();

    // ----------- Calcul du vecteur normal selon le type de collision -----------
    if (selfType == ColliderType::Rectangle && otherType == ColliderType::Rectangle)
    {
        BoxCollider* a = static_cast<BoxCollider*>(_self);
        BoxCollider* b = static_cast<BoxCollider*>(_other);

        float dx = selfPos.GetX() - otherPos.GetX();
        float dy = selfPos.GetY() - otherPos.GetY();

        float overlapX = (a->GetWidth() * 0.5f + b->GetWidth() * 0.5f) - std::abs(dx);
        float overlapY = (a->GetHeight() * 0.5f + b->GetHeight() * 0.5f) - std::abs(dy);

        if (overlapX < overlapY)
        {
            normal = (dx < 0) ? Vector2f(-1, 0) : Vector2f(1, 0);
            penetrationDepth = overlapX;
        }
        else
        {
            normal = (dy < 0) ? Vector2f(0, -1) : Vector2f(0, 1);
            penetrationDepth = overlapY;
        }
    }
    else if (selfType == ColliderType::Circle && otherType == ColliderType::Circle)
    {
        CircleCollider* a = static_cast<CircleCollider*>(_self);
        CircleCollider* b = static_cast<CircleCollider*>(_other);

        Vector2f delta = selfPos - otherPos;
        float dist = delta.Length();
        float r = a->GetRadius() + b->GetRadius();

        if (dist != 0)
            normal = delta / dist;
        else
            normal = Vector2f(0, -1);

        penetrationDepth = r - dist;
    }
    else
    {
        // Box <-> Circle
        BoxCollider* box = (selfType == ColliderType::Rectangle ? static_cast<BoxCollider*>(_self) : static_cast<BoxCollider*>(_other));
        CircleCollider* circle = (selfType == ColliderType::Circle ? static_cast<CircleCollider*>(_self) : static_cast<CircleCollider*>(_other));

        Vector2f boxPos = box->GetOwner()->GetComponent<TransformComponent>()->GetPos() + box->GetOffset();
        Vector2f circlePos = circle->GetOwner()->GetComponent<TransformComponent>()->GetPos() + circle->GetOffset();

        float halfW = box->GetWidth() * 0.5f;
        float halfH = box->GetHeight() * 0.5f;

        // Clamp du centre du cercle au rectangle
        float clampedX = std::max(boxPos.GetX() - halfW,
            std::min(circlePos.GetX(), boxPos.GetX() + halfW));
        float clampedY = std::max(boxPos.GetY() - halfH,
            std::min(circlePos.GetY(), boxPos.GetY() + halfH));

        Vector2f closest(clampedX, clampedY);
        Vector2f delta = circlePos - closest;

        float dist = delta.Length();
        normal = (dist != 0) ? delta / dist : Vector2f(0, -1);

        penetrationDepth = circle->GetRadius() - dist;

        if (selfType == ColliderType::Rectangle)
            normal = normal * -1;
    }

    if (penetrationDepth <= 0)
        return;

    // ---------------- SAFE MARGIN + POSITION CORRECTION ----------------
    float invMassA = m_isKinematic ? 0.0f : 1.0f / m_mass;
    float invMassB = (otherRb && !otherRb->m_isKinematic) ? 1.0f / otherRb->m_mass : 0.0f;

    float correctionPercent = 1.f;
    float slop = m_safeMargin;

    float correctionMag = std::max(penetrationDepth - slop, 0.0f) / (invMassA + invMassB) * correctionPercent;
    Vector2f correction = normal * correctionMag;

    if (!m_isKinematic)
        selfTransform->SetPos(selfTransformPos + correction * invMassA);

    if (otherRb && !otherRb->m_isKinematic)
        otherTransform->SetPos(otherTransformPos - correction * invMassB);

    Vector2f horizontalNormal = { normal.GetX(), 0 };
    m_velocity = m_velocity - horizontalNormal * m_velocity.Dot(horizontalNormal);

    Vector2f verticalNormal = { 0, normal.GetY() };
    m_velocity = m_velocity - verticalNormal * m_velocity.Dot(verticalNormal);

    // ----------- Calcul de la vélocité relative -----------
    Vector2f otherVelocity = otherRb ? otherRb->m_velocity : Vector2f(0, 0);
    Vector2f relativeVelocity = m_velocity - otherVelocity;

    float velAlongNormal = relativeVelocity.Dot(normal);

    if (velAlongNormal > 0)
        return;

    // ----------- Calcul de l'impulsion -----------

    float restitution = otherRb ? std::min(m_restitution, otherRb->m_restitution) : m_restitution;

    float j = -(1 + restitution) * velAlongNormal / (invMassA + invMassB);
    Vector2f impulse = normal * j;

    // ----------- Applique l'impulsion -----------
    AddImpulse(impulse);

    if (otherRb && !otherRb->m_isKinematic)
    {
        Vector2f ref{ 0, 0 };
        otherRb->AddImpulse(ref - impulse);
    }
}



