#define SDL_MAIN_HANDLED
#include <iostream>
#include "Application.h"
#include "SceneManager.h"
#include "StartScene.h"
#include "LevelTestScene.h"
#include "LevelSelectorScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "Level3Scene.h"
#include "Level4Scene.h"
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

    ae.LoadSound("UI_HOVER", "./Assets/UI_Hover.wav");
    ae.LoadSound("UI_CLICK", "./Assets/UI_Click.wav");
    ae.LoadSound("BUTTON_DOWN", "./Assets/button_down.wav");
    ae.LoadSound("BUTTON_UP", "./Assets/button_up.wav");
    ae.LoadSound("PICK_UP", "./Assets/Pick_Up.wav");
    ae.LoadSound("WALKING", "./Assets/walking.wav");
    ae.LoadSound("DEATH", "./Assets/Death_SFX.wav");
    ae.LoadSound("PORTAL_OPEN", "./Assets/Portal_Open.wav");
    ae.LoadSound("PORTAL_CLOSE", "./Assets/Portal_Close.wav");
    ae.LoadSound("SPIRIT_IN", "./Assets/Spirit_In.wav");
    ae.LoadSound("SPIRIT_OUT", "./Assets/Spirit_Out.wav");

    ae.LoadMusic("MAIN", "./Assets/mainMusic.wav");

    ae.PlayMusic("MAIN", true);

    SceneManager& sm = SceneManager::GetInstance();

    sm.AddScene("StartScene", new StartScene);
    sm.AddScene("LevelTestScene", new LevelTestScene);
    sm.AddScene("LevelSelectorScene", new LevelSelectorScene);
    sm.AddScene("Level1Scene", new Level1Scene);
    sm.AddScene("Level2Scene", new Level2Scene);
    sm.AddScene("Level3Scene", new Level3Scene);
    sm.AddScene("Level4Scene", new Level4Scene);

    sm.SetStartScene("StartScene");

    app.LoopApp();
	return 0;
}