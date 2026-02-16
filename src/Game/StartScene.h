#pragma once
#include "AScene.h"
#include "Entity.h"

class StartScene : public AScene
{
    Entity* m_backGround;
    Entity* m_quitButton;
    Entity* m_singleButton;
    Entity* m_multiButton;

    Entity* m_title;

public:
    StartScene();
    void Enter() override;
    void Exit() override;
};