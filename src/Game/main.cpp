#define SDL_MAIN_HANDLED
#include <iostream>
#include "main.h"
#include "Application.h"
#include "SceneManager.h"
#include "StartScene.h"
#include "LevelScene.h"
#include "EndScene.h"
#include "Lib2D/AudioEngine.h"

int main()
{
    srand(time(NULL));
    rand();

    Application& app = Application::Get();
    app.InitApp("Pong", 1300, 800);

    AudioEngine& ae = AudioEngine::Get();

    if (ae.Init() == false)
        exit(1);

    ae.LoadSound("WOOD_HIT", "../../Assets/woodHit.wav");
    ae.LoadSound("ROCK_HIT", "../../Assets/rockHit.wav");
        
    SceneManager& sm = SceneManager::GetInstance();

    sm.AddScene("START", new StartScene);
    sm.AddScene("LEVEL", new LevelScene);
    sm.AddScene("GAME_OVER", new EndScene);

    sm.SetStartScene("START");

    app.LoopApp();
    return 0;
}