#define SDL_MAIN_HANDLED
#include <iostream>
#include "Application.h"
#include "SceneManager.h"
#include "LevelTestScene.h"
#include "Level1Scene.h"
#include "Lib2D/AudioEngine.h"

int main()
{
    srand(time(NULL));
    rand();

    Application& app = Application::Get();
    app.InitApp("Pong", 1920, 1080);

    AudioEngine& ae = AudioEngine::Get();

    if (ae.Init() == false)
        exit(1);

    ae.SetMasterVolume(5);

    ae.LoadMusic("MAIN", "../../Assets/mainMusic.wav");

    ae.PlayMusic("MAIN", true);

    SceneManager& sm = SceneManager::GetInstance();

    sm.AddScene("LevelTestScene", new LevelTestScene);
    sm.AddScene("Level1Scene", new Level1Scene);

    sm.SetStartScene("Level1Scene");

    app.LoopApp();
	return 0;
}