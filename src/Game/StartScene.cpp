#include "StartScene.h"
#include "AllComponent.h"
#include "QuitButtonComponent.h"
#include "StartSingleButtonComponent.h"
#include "StartMultiButtonComponent.h"
#include "TextComponent.h"

StartScene::StartScene()
{
    m_backGround = CreateEntity();
    SpriteRenderer* sr = m_backGround->AddComponent<SpriteRenderer>();
    sr->Load("../../Assets/StartBackground.jpg");

    m_title = CreateEntity();
    TextComponent* tc = m_title->AddComponent<TextComponent>("../../Assets/Bungee-Regular.otf", 100);
    tc->SetDrawColor(243, 255, 94,255);
    tc->SetText("Pong");

    m_singleButton = CreateButton(200, 100);
    m_singleButton->AddComponent<SpriteRenderer>()->Load("../../Assets/Sprites-Button/png/Dummy-Rect/Hover.png");
    m_singleButton->GetComponent<TransformComponent>()->SetScale(1.2f);
    m_singleButton->AddComponent<TextComponent>("../../Assets/Bungee-Regular.otf", 42)->SetText("Single");
    m_singleButton->AddComponent<StartSingleButtonComponent>();

    m_multiButton = CreateButton(200, 100);
    m_multiButton->AddComponent<SpriteRenderer>()->Load("../../Assets/Sprites-Button/png/Dummy-Rect/Hover.png");
    m_multiButton->GetComponent<TransformComponent>()->SetScale(1.2f);
    m_multiButton->AddComponent<TextComponent>("../../Assets/Bungee-Regular.otf", 45)->SetText("Multi");
    m_multiButton->AddComponent<StartMultiButtonComponent>();

    m_quitButton = CreateButton(200, 100);
    m_quitButton->AddComponent<SpriteRenderer>()->Load("../../Assets/Sprites-Button/png/Dummy-Rect/Hover.png");
    m_quitButton->GetComponent<TransformComponent>()->SetScale(1.2f);
    m_quitButton->AddComponent<TextComponent>("../../Assets/Bungee-Regular.otf", 45)->SetText("Quit");
    m_quitButton->AddComponent<QuitButtonComponent>();
}

void StartScene::Enter()
{
    m_singleButton->GetComponent<TransformComponent>()->SetPos({ 525, 500 });
    m_multiButton->GetComponent<TransformComponent>()->SetPos({ 775, 500 });
    m_backGround->GetComponent<TransformComponent>()->SetPos({ 650, 450 });
    m_quitButton->GetComponent<TransformComponent>()->SetPos({ 650, 620 });
    m_title->GetComponent<TransformComponent>()->SetPos({ 650, 300 });

}

void StartScene::Exit()
{
}