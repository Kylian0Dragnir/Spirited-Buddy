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
	InputManager& im = InputManager::Get();
	SceneManager& sm = SceneManager::GetInstance();
	AScene* cs = sm.GetCurrentScene();

	if (m_player == nullptr) m_player = cs->FindByTag("Player");

	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();



	float dx = 0;
	float dy = 0;

	if (im.IsKeyDown(m_switchKey))
	{
		dynamic_cast<MainScene*>(cs)->SwitchMode();
		m_mousePos = im.GetMousePosition();
		if (dynamic_cast<MainScene*>(cs)->GetMode())
			transform->SetPos(m_player->GetComponent<TransformComponent>()->GetPos());
		else
			transform->SetPos({ -100,-100 });
	}

	if (dynamic_cast<MainScene*>(cs)->GetMode())
	{
		dx = im.GetMousePosition().GetX() - m_mousePos.GetX();
		dy = im.GetMousePosition().GetY() - m_mousePos.GetY();
		m_mousePos = im.GetMousePosition();
	}

	transform->Translate(dx, dy);
}

void SpiritMovement::OnCollisionStay(Collider* _self, Collider* _other)
{
}
