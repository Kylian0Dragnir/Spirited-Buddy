#define SDL_MAIN_HANDLED
#include <iostream>
#include "Application.h"
#include "SceneManager.h"
#include "StartScene.h"
#include "LevelTestScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "Level3Scene.h"
#include "Lib2D/AudioEngine.h"

int main()
{
    srand(time(NULL));
    rand();

    Application& app = Application::Get();
    app.InitApp("Spirited Buddy", 1920, 1080);

    AudioEngine& ae = AudioEngine::Get();

    if (ae.Init() == false)
        exit(1);

    ae.SetMasterVolume(5);

    ae.LoadSound("DEATH", "../../Assets/Death_SFX.wav");
    ae.LoadMusic("MAIN", "../../Assets/mainMusic.wav");

    ae.PlayMusic("MAIN", true);

    SceneManager& sm = SceneManager::GetInstance();

    sm.AddScene("StartScene", new StartScene);
    sm.AddScene("LevelTestScene", new LevelTestScene);
    sm.AddScene("Level1Scene", new Level1Scene);
    sm.AddScene("Level2Scene", new Level2Scene);
    sm.AddScene("Level3Scene", new Level3Scene);

    sm.SetStartScene("StartScene");

    app.LoopApp();
	return 0;
}