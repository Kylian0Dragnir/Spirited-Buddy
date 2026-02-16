#include "AiMovement.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "Collider.h"
#include "TagComponent.h"
#include "SceneManager.h"
#include "AScene.h"

AiMovement::AiMovement()
{
	m_direction = { 0, 0 };
	m_speed = 0.9f;
	m_entityFollow = SceneManager::GetInstance().GetCurrentScene()->FindByTag("BALL");
}

void AiMovement::Update(float _dt)
{
	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
	TransformComponent* followTransform = m_entityFollow->GetComponent<TransformComponent>();

	if (transform->GetPos().GetY() - followTransform->GetPos().GetY() > 0)
	{
		m_direction.SetY(-1);
	}
	else
	{
		m_direction.SetY(1);
	}

	float dy = _dt * m_direction.GetY() * m_speed * 500;
	transform->Translate(0, dy);
}

void AiMovement::OnCollisionStay(Collider* _self, Collider* _other)
{
	Entity* otherEntity = _other->GetOwner();

	TagComponent* otherEntityTag = otherEntity->GetComponent<TagComponent>();

	if (otherEntityTag)
	{
		if (otherEntityTag->Is("WALL1"))
		{
			TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
			transform->Translate(0, 7);
		}

		else if (otherEntityTag->Is("WALL2"))
		{
			TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
			transform->Translate(0, -7);
		}
	}
}
