#include "CakeLogic.h"
#include "Lib2D/InputManager.h"
#include "TextComponent.h"
#include "SpriteRenderer.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Entity.h"
#include "TagComponent.h"
#include "SceneManager.h"
#include "AScene.h"

void CakeLogic::Update(float _dt)
{
	if (m_timer > 0)
	{
		m_timer -= _dt;
		
		if (m_timer <= 0)
		{
			SceneManager::GetInstance().GetCurrentScene()->DestroyEntity(m_owner);
		}
	}
}

void CakeLogic::OnCollisionStay(Collider* _self, Collider* _other)
{
	if (_other->GetOwner()->GetComponent<TagComponent>()->Is("Player") == false)
		return;

	if (InputManager::Get().IsKeyDown(Key::KEY_e))
	{
		m_owner->GetComponent<SpriteRenderer>()->SetVisible(false);
		m_owner->GetComponent<BoxCollider>()->SetActive(false);
		m_owner->GetComponent<TextComponent>()->SetVisible(true);
		m_timer = 2.f;
	}
}
