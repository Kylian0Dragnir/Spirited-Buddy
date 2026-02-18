#include "PortalLogic.h"
#include "Lib2D/InputManager.h"
#include "SpriteRenderer.h"
#include "Entity.h"
#include "Collider.h"
#include "Rigidbody2D.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "MainScene.h"
#include "TilemapLoader.h"

void PortalLogic::Update(float dt)
{
	SpriteRenderer* sr = m_owner->GetComponent<SpriteRenderer>();

	if (m_teleportRequested == false)
	{
		sr->SetFrame(64, 64, m_frameX, m_frameY);
		return;
	}

	if (m_frameX >= 512)
		return;

	if (m_timer <= 0)
	{
		sr->SetFrame(64, 64, m_frameX, m_frameY);
		m_frameX += 64;
		m_timer = 0.05f;
	}
	else
	{
		m_timer -= dt;
	}
}

void PortalLogic::OnCollisionStay(Collider* _self, Collider* _other)
{
	if (InputManager::Get().IsKeyDown(Key::KEY_e) && static_cast<MainScene*>(SceneManager::GetInstance().GetCurrentScene())->GetMode() == false)
	{
		m_teleportRequested = true;
		_other->GetOwner()->GetComponent<TransformComponent>()->SetPos({ 100, 100 });
		_other->GetOwner()->GetComponent<Rigidbody2D>()->AddImpulse({0,1000});
	}
}
