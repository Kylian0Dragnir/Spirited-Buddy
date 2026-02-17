#include "Application.h"
#include "Window.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "AScene.h"
#include "CollisionSystem.h"
#include "Timer.h"
#include "Windows.h"

Application::Application()
{ 
    m_window = nullptr;
}

Application::~Application()
{
    delete m_window;
}

Application& Application::Get()
{
    static Application Instance;
    return Instance;
}

void Application::InitApp(const std::string& _title, int _width, int _height, int _targetFPS)
{
    m_FPS = _targetFPS;
    m_window = new Window;
    m_window->Create(_title, _width, _height, 100, 100);
}

void Application::LoopApp()
{
    SceneManager& sm = SceneManager::GetInstance();
    CollisionSystem cs;
    Timer frameTimer;

    frameTimer.StartTime();

    while (m_window->GetIsOpen())
    {
        float deltaTime = frameTimer.Restart();

        InputManager& im = InputManager::Get();
        im.Update();

        if (im.IsKeyDown(Key::KEY_ESCAPE))
            ShutDownApp();

        cs.Update(sm.GetCurrentScene()->GetEntities());

        sm.Update(deltaTime);

        m_window->ClearWindow();

        m_window->Draw(&sm);

        m_window->Display();

        float diff = (1.f / m_FPS) - deltaTime;

        //Cap FPS
        if (diff > 0)
        {
            Sleep(diff * 1000);
        }
    }
}

void Application::ShutDownApp()
{
    m_window->SetIsOpen(false);
}
