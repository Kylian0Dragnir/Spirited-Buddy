#define SDL_MAIN_HANDLED
#include <iostream>
#include "Application.h"
#include "SceneManager.h"
#include "LevelTestScene.h"
#include "Lib2D/AudioEngine.h"

int main()
{
    srand(time(NULL));
    rand();

    Application& app = Application::Get();
    app.InitApp("Pong", 1920, 1080);

    SceneManager& sm = SceneManager::GetInstance();

    sm.AddScene("LevelTestScene", new LevelTestScene);

    sm.SetStartScene("LevelTestScene");

    app.LoopApp();
	return 0;
}