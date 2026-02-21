#include "WorldWrapLogic.h"
#include "Entity.h"
#include "Collider.h"
#include "SceneManager.h"
#include "AScene.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "TransformComponent.h"
#include <iostream>
#include <algorithm>
#include "TagComponent.h"

WorldWrapLogic::WorldWrapLogic()
{
	m_clone = nullptr;
}

void WorldWrapLogic::Update(float _dt)
{
	if (m_clone == nullptr)
		return;

	TransformComponent* cloneTransform = m_clone->GetComponent<TransformComponent>();
	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
	Vector2f ownerPos = transform->GetPos();

	if (std::min(abs(ownerPos.GetX() - 1920), ownerPos.GetX()) < std::min(abs(ownerPos.GetY() - 1080), ownerPos.GetY()))
	{
		if (ownerPos.GetX() > 1920 / 2)
			cloneTransform->SetPos({ ownerPos.GetX() - 1920, ownerPos.GetY() });
		else
			cloneTransform->SetPos({ ownerPos.GetX() + 1920, ownerPos.GetY() });
	}
	else
	{
		if (ownerPos.GetY() > 1080 / 2)
			cloneTransform->SetPos({ ownerPos.GetX(), ownerPos.GetY() - 1080 });
		else
			cloneTransform->SetPos({ ownerPos.GetX(), ownerPos.GetY() + 1080 });
	}

	Collider* ownerCollider = m_owner->GetComponent<Collider>();

	float ownerWidthMiddle = 0;
	float ownerHeightMiddle = 0;

	if (ownerCollider->GetType() == ColliderType::Rectangle)
	{
		ownerWidthMiddle = static_cast<BoxCollider*>(ownerCollider)->GetWidth() / 2;
		ownerHeightMiddle = static_cast<BoxCollider*>(ownerCollider)->GetHeight() / 2;
	}

	if (transform->GetPos().GetX() - ownerWidthMiddle > 1920)
		transform->SetPos({ transform->GetPos().GetX() - 1920, transform->GetPos().GetY() });
	if (transform->GetPos().GetX() + ownerWidthMiddle < 0 )
		transform->SetPos({ transform->GetPos().GetX() + 1920, transform->GetPos().GetY() });
	if (transform->GetPos().GetY() - ownerHeightMiddle > 1080)
		transform->SetPos({ transform->GetPos().GetX(), transform->GetPos().GetY() - 1080 });
	if (transform->GetPos().GetY() + ownerHeightMiddle < 0 )
		transform->SetPos({ transform->GetPos().GetX(), transform->GetPos().GetY() + 1080 });
}

void WorldWrapLogic::Generate()
{
	m_clone = SceneManager::GetInstance().GetCurrentScene()->CreateEntity();

	m_owner->GetComponent<TagComponent>()->AddTag("WORLD_WRAP");

	std::vector<Collider*> ownerColliders = m_owner->GetAllComponents<Collider>();

	for (Collider* col : ownerColliders)
	{
		switch (col->GetType())
		{
		case ColliderType::Rectangle:
		{
			BoxCollider* bc = static_cast<BoxCollider*>(col);
			BoxCollider* cbc = m_clone->AddComponent<BoxCollider>(bc->GetWidth(), bc->GetHeight(), bc->GetLayer(), bc->GetMask());
			cbc->SetVisible(true);
			cbc->SetOffset(bc->GetOffset().GetX(), bc->GetOffset().GetY());
			cbc->SetActive(bc->IsActived());
			cbc->SetTrigger(bc->IsTrigger());
			
		}
		break;

		case ColliderType::Circle:
		{
			CircleCollider* cc = static_cast<CircleCollider*>(col);
			CircleCollider* ccc = m_clone->AddComponent<CircleCollider>(cc->GetRadius(), cc->GetLayer(), cc->GetMask());
			ccc->SetVisible(true);
			ccc->SetOffset(cc->GetOffset().GetX(), cc->GetOffset().GetY());
			ccc->SetActive(cc->IsActived());
			ccc->SetTrigger(cc->IsTrigger());
		}
		break;
		}
	}
}