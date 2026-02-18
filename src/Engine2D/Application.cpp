#include "Application.h"
#include "Window.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "AScene.h"
#include "CollisionSystem.h"
#include "Timer.h"
#include "Windows.h"

using Clock = std::chrono::steady_clock;

float GetElapsed(Clock::time_point& _start, float targetFps)
{
    while (true)
    {
        auto duration = Clock::now() - _start;

        if (duration.count() >= 1000000000.f / targetFps)
            return duration.count() / 1000000000.f;
    }
}

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
    CollisionSystem& cs = CollisionSystem::GetInstance();

    float deltaTime = 0;

    while (m_window->GetIsOpen())
    {
        Clock::time_point start = Clock::now();

        InputManager& im = InputManager::Get();
        im.Update(deltaTime);

        if (im.IsKeyDown(Key::KEY_ESCAPE))
            ShutDownApp();

        sm.Update(deltaTime);

        cs.Update(sm.GetCurrentScene()->GetEntities());

        m_window->ClearWindow();

        m_window->Draw(&sm);

        m_window->Display();

        deltaTime = GetElapsed(start, m_FPS);
    }
}

void Application::ShutDownApp()
{
    m_window->SetIsOpen(false);
}
