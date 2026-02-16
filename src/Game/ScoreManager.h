#pragma once
#include "Component.h"
#include "Lib2D/Vector2f.h"

class ScoreManager : public Component
{
    int m_scoreP1 = 0;
    int m_scoreP2 = 0;

public:

    void AddPointPlayer1();
    void AddPointPlayer2();

    void ResetBall();

    int GetScoreP1() const;
    int GetScoreP2() const;

    void SetText();

    bool CheckGameOver();
    void Reset();
};


