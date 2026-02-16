#include "RestartButtonComponent.h"
#include "SceneManager.h"

void RestartButtonComponent::OnClick(ButtonComponent* _button)
{
	SceneManager::GetInstance().ChangeScene("START");
}
