#define SDL_MAIN_HANDLED
#include "main.h"
#include "Entity.h"
#include "Lib2D/Window.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "Lib2D/Sprite.h"
#include "Lib2D/InputManager.h"
#include "Lib2D/AssetManager.h"
#include "Rigidbody2D.h"
#include "Timer.h"
#include "CollisionSystem.h"

int main()
{
    Window w;
    w.Create("Test", 800, 800, 100, 100);

    AssetManager::Get().SetWindow(&w);
    CollisionSystem colsys;

    Entity* e1 = new Entity();
    TransformComponent* tc = e1->AddComponent<TransformComponent>();
    BoxCollider* bc = e1->AddComponent<BoxCollider>(135, 200);
    SpriteRenderer* sr = e1->AddComponent<SpriteRenderer>();
    Rigidbody2D* rb = e1->AddComponent<Rigidbody2D>();

    Entity* e2 = new Entity();
    TransformComponent* tc2 = e2->AddComponent<TransformComponent>();
    CircleCollider* bc2 = e2->AddComponent<CircleCollider>(100);
    Rigidbody2D* rb2 = e2->AddComponent<Rigidbody2D>();

    tc2->SetPos({ 250, 650 });
    rb2->SetKinematic(true);

    tc->SetPos({ 400, 100 });
    sr->Load("../../Assets/maelle.png");

    InputManager& im = InputManager::Get();

    Timer frameTimer;

    frameTimer.StartTime();

    std::vector<Entity*> entities;
    entities.push_back(e1);
    entities.push_back(e2);
    
    while (w.GetIsOpen())
    {
        float deltaTime = frameTimer.Restart();

        im.Update();
        rb->Update(deltaTime);
        rb2->Update(deltaTime);
        rb->AddImpulse({ 0, 0.2f });
        colsys.Update(entities);

        if (im.IsKeyDown(Key::KEY_ESCAPE))
        {
            w.SetIsOpen(false);
        }

        if (im.IsKeyHeld(Key::KEY_z))
        {
            tc->SetPos({ tc->GetPos().GetX(), tc->GetPos().GetY() - 0.01f });
        }

        if (bc->GetBottom() < 0)
        {
            w.SetIsOpen(false);
        }

        w.ClearWindow();

        w.Draw(sr);
        w.Draw(bc);
        w.Draw(bc2);

        w.Display();
    }

    delete e1;
    delete e2;

    return 0;
}