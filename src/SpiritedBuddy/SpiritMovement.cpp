#include "SpiritMovement.h"
#include "Lib2D/InputManager.h"
#include "SceneManager.h"
#include "TransformComponent.h"
#include "TagComponent.h"
#include "Rigidbody2D.h"
#include "Collider.h"
#include "Entity.h"
#include "Player.h"
#include "MainScene.h"
#include <iostream>

SpiritMovement::SpiritMovement(Key _switchKey)
{
	m_switchKey = _switchKey;
	m_speed = 1.2f;
	m_player = nullptr;

}

void SpiritMovement::Update(float _dt)
{
	MainScene* cs = static_cast<MainScene*>(SceneManager::GetInstance().GetCurrentScene());
	InputManager& im = InputManager::Get();
	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();

	if (m_player == nullptr)
		m_player = cs->FindByTag("Player");

	if (m_player == nullptr)
		return;


	if (im.IsKeyDown(m_switchKey))
	{
		cs->SwitchMode();
		if (cs->GetMode()) {
			transform->SetPos(m_player->GetComponent<TransformComponent>()->GetPos() + Vector2f{ 0, -40});
			im.SetMousePosition(m_player->GetComponent<TransformComponent>()->GetPos() + Vector2f{ 0, -40});
		}
		else
			transform->SetPos({ -100,-100 });
	}

	if (cs->GetMode() == false)
		return;

	transform->SetPos(im.GetMousePosition());
}

void SpiritMovement::OnCollisionStay(Collider* _self, Collider* _other)
{
}
