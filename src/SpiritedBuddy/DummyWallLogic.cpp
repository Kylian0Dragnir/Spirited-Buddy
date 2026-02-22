#include "DummyWallLogic.h"
#include "TagComponent.h"
#include "Collider.h"
#include "Entity.h"
#include "SpriteRenderer.h"
#include "SceneManager.h"
#include "AScene.h"

void DummyWallLogic::Update(float _dt)
{
	if (m_playerCollide)
	{
		m_owner->GetComponent<SpriteRenderer>()->SetOpacity(m_currentOpacity);
		m_currentOpacity -= 5;

		if (m_currentOpacity <= 40)
			SceneManager::GetInstance().GetCurrentScene()->DestroyEntity(m_owner);
	}
}

void DummyWallLogic::OnCollisionEnter(Collider* _self, Collider* _other)
{
	if (_other->IsTrigger())
		return;

	TagComponent* otherTag = _other->GetOwner()->GetComponent<TagComponent>();
	if (otherTag && (otherTag->Is("Player") || otherTag->Is("Spirit")))
	{
		m_playerCollide = true;
	}
}
