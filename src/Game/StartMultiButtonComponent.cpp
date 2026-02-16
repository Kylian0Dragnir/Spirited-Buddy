#include "StartMultiButtonComponent.h"
#include "SceneManager.h"
#include "LevelScene.h"

void StartMultiButtonComponent::OnClick(ButtonComponent* _button)
{
	SceneManager& sm = SceneManager::GetInstance();
	sm.ChangeScene("LEVEL");
	LevelScene* ls = static_cast<LevelScene*>(sm.FindSceneById("LEVEL"));
	ls->SetMultiplayer(true);
}
