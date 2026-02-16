#include "EndScene.h"
#include "AllComponent.h"
#include "QuitButtonComponent.h"
#include "RestartButtonComponent.h"

EndScene::EndScene()
{
    m_backGround = CreateEntity();
    m_backGround->AddComponent<SpriteRenderer>()->Load("../../Assets/EndBackground.jpg");
    m_backGround->GetComponent<TransformComponent>()->SetScale(1);

    m_title = CreateEntity();
    TextComponent* tc = m_title->AddComponent<TextComponent>("../../Assets/Bungee-Regular.otf", 100);
    tc->SetDrawColor(243, 255, 94, 255);
    tc->SetText("Game Over");

    m_quitButton = CreateButton(200, 100);
    m_quitButton->AddComponent<SpriteRenderer>()->Load("../../Assets/Sprites-Button/png/Dummy-Rect/Hover.png");
    m_quitButton->GetComponent<TransformComponent>()->SetScale(1.2f);
    m_quitButton->AddComponent<TextComponent>("../../Assets/Bungee-Regular.otf", 45)->SetText("Quit");
    m_quitButton->AddComponent<QuitButtonComponent>();

}

void EndScene::Enter()
{
    m_backGround->GetComponent<TransformComponent>()->SetPos({ 650, 450 });
    m_quitButton->GetComponent<TransformComponent>()->SetPos({ 650, 550 });
    m_title->GetComponent<TransformComponent>()->SetPos({ 650, 300 });
}

void EndScene::Exit()
{
}