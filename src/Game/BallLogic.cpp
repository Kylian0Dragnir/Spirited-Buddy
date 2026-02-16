#include "BallLogic.h"
#include "Entity.h"
#include "AllComponent.h"

void BallLogic::ServeRandom(float speed)
{
    float dirX = (rand() % 2 == 0) ? -1.f : 1.f;
    float dirY = ((rand() % 200) - 100) / 100.f;

    Vector2f dir(dirX, dirY);
    dir = dir.Normalize();

    m_owner->GetComponent<Rigidbody2D>()->AddImpulse(dir * speed * 500.f);
}

void BallLogic::Reset()
{
    TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
    Rigidbody2D* rb = m_owner->GetComponent<Rigidbody2D>();

    transform->SetPos({ 650, 400 });
    rb->SetVelocity({ 0,0 });

    ServeRandom(2.f);
}

void BallLogic::OnCollisionEnter(Collider* _self, Collider* _other)
{
    Vector2f pos = m_owner->GetComponent<TransformComponent>()->GetPos();
    AudioSource* as = m_owner->GetComponent<AudioSource>();

    if (TagComponent* tag = _other->GetOwner()->GetComponent<TagComponent>())
    {
        if (tag->Is("WALL1") || tag->Is("WALL2"))
        {
            as->Play("WOOD_HIT");
        }
        else if (tag->Is("ROCK"))
        {
            as->Play("ROCK_HIT");
        }
    }
}