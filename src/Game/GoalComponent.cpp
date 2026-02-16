#include "GoalComponent.h"
#include "Entity.h"
#include "Collider.h"
#include "TagComponent.h"
#include "SceneManager.h"
#include "AScene.h"
#include "ScoreManager.h"

void GoalComponent::OnCollisionEnter(Collider* _self, Collider* _other)
{
    TagComponent* otherTag = _other->GetOwner()->GetComponent<TagComponent>();
    if (otherTag == nullptr) 
        return;

    TagComponent* tag = m_owner->GetComponent<TagComponent>();

    if (otherTag->Is("BALL"))
    {
        ScoreManager* sm = SceneManager::GetInstance().GetCurrentScene()->FindByTag("SCORE_MANAGER")->GetComponent<ScoreManager>();

        if (tag->Is("LEFT_GOAL"))
            sm->AddPointPlayer2();

        else if (tag->Is("RIGHT_GOAL"))
            sm->AddPointPlayer1();
    }
}
