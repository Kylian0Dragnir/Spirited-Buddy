#include "CollectibleLogic.h"
#include "TagComponent.h"
#include "Collider.h"
#include "Entity.h"
#include "AScene.h"
#include "SceneManager.h"

void CollectibleLogic::OnCollisionEnter(Collider* _self, Collider* _other)
{
	TagComponent* otherEntityTag = _other->GetOwner()->GetComponent<TagComponent>();
	if (otherEntityTag && (otherEntityTag->Is("Player") || otherEntityTag->Is("Spirit")))
	{
		AScene* cs = SceneManager::GetInstance().GetCurrentScene();
		cs->DestroyEntity(m_owner);
	}

}
