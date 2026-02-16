#include "ScoreManager.h"
#include "SceneManager.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "Rigidbody2D.h"
#include "AiMovement.h"
#include "AScene.h"
#include "Entity.h"
#include "BallLogic.h"

void ScoreManager::AddPointPlayer1()
{
    m_scoreP1++;
    SetText();

    if(CheckGameOver())
    {
        SceneManager::GetInstance().ChangeScene("GAME_OVER");
        return;
    }

    ResetBall();
}

void ScoreManager::AddPointPlayer2()
{
    m_scoreP2++;
    SetText();

    if (CheckGameOver())
    {
        SceneManager::GetInstance().ChangeScene("GAME_OVER");
        return;
    }

    ResetBall();
}

void ScoreManager::ResetBall()
{
    Entity* ball = SceneManager::GetInstance().GetCurrentScene()->FindByTag("BALL");
    ball->GetComponent<BallLogic>()->Reset();
}

int ScoreManager::GetScoreP1() const { return m_scoreP1; }

int ScoreManager::GetScoreP2() const { return m_scoreP2; }

void ScoreManager::SetText()
{
    TextComponent* tc = m_owner->GetComponent<TextComponent>();
    tc->SetDrawColor(250, 200, 152, 255);
    tc->SetText(std::to_string(m_scoreP1) + " - " + std::to_string(m_scoreP2));  
}

bool ScoreManager::CheckGameOver()
{
    if (m_scoreP1 >= 5 || m_scoreP2 >= 5)
        return true;

    return false;
}

void ScoreManager::Reset()
{
    m_scoreP1 = 0;
    m_scoreP2 = 0;
    SetText();
    ResetBall();
}

