#pragma once
#include "AScene.h"
#include "Entity.h"

class EndScene : public AScene
{
    Entity* m_backGround;
    Entity* m_quitButton;
    Entity* m_title;

public:
    EndScene();
    void Enter() override;
    void Exit() override;
};