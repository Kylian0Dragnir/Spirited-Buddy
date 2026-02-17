#include "CollectibleLogic.h"
#include "TagComponent.h"
#include "Collider.h"
#include "Entity.h"
#include "MainScene.h"
#include "SceneManager.h"

void CollectibleLogic::OnCollisionEnter(Collider* _self, Collider* _other)
{
	TagComponent* otherEntityTag = _other->GetOwner()->GetComponent<TagComponent>();
	if (otherEntityTag && (otherEntityTag->Is("Player") || otherEntityTag->Is("Spirit")))
	{
		MainScene* cs = static_cast<MainScene*>(SceneManager::GetInstance().GetCurrentScene());
		cs->DestroyCollectible(m_owner);
	}

}
