#include "QuitButtonComponent.h"
#include "Application.h"

void QuitButtonComponent::OnClick(ButtonComponent* _button)
{
	Application::Get().ShutDownApp();
}
