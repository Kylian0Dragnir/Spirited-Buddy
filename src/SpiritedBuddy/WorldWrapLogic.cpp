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


	system("cls");

	if (std::min(abs(ownerPos.GetX() - 1920), ownerPos.GetX()) < std::min(abs(ownerPos.GetY() - 1080), ownerPos.GetY()))
	{
		if (ownerPos.GetX() > 1920 / 2)
		{
			cloneTransform->SetPos({ ownerPos.GetX() - 1920, ownerPos.GetY() });
			std::cout << "Right" << std::endl;
		}
		else
		{
			cloneTransform->SetPos({ ownerPos.GetX() + 1920, ownerPos.GetY() });
			std::cout << "Left" << std::endl;
		}
	}
	else
	{
		if (ownerPos.GetY() > 1080 / 2)
		{
			cloneTransform->SetPos({ ownerPos.GetX(), ownerPos.GetY() - 1080 });
			std::cout << "Bottom" << std::endl;
		}
		else
		{
			cloneTransform->SetPos({ ownerPos.GetX(), ownerPos.GetY() + 1080 });
			std::cout << "Top" << std::endl;
		}
	}

	std::cout << "Player : " << ownerPos.GetX() << " " << ownerPos.GetY() << std::endl;
	std::cout << "Clone : " << cloneTransform->GetPos().GetX() << " " << cloneTransform->GetPos().GetY();

	Collider* ownerCollider = m_owner->GetComponent<Collider>();

	float ownerMiddle = 0;

	if (ownerCollider->GetType() == ColliderType::Circle)
		ownerMiddle = ownerPos.GetY();
	else if (ownerCollider->GetType() == ColliderType::Rectangle)
		ownerMiddle = static_cast<BoxCollider*>(ownerCollider)->GetWidth() / 2;

	if (ownerPos.GetX() > 1920 + ownerMiddle)
		transform->SetPos({ ownerPos.GetX() - 1920, ownerPos.GetY() });
	if (ownerPos.GetX() < 0 - ownerMiddle)
		transform->SetPos({ ownerPos.GetX() + 1920, ownerPos.GetY() });
}

void WorldWrapLogic::Generate()
{
	m_clone = SceneManager::GetInstance().GetCurrentScene()->CreateEntity();

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