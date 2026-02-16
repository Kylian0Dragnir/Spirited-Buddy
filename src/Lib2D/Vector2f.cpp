#include "Vector2f.h"
#include <iostream>

Vector2f::Vector2f(float _x, float _y) : m_x(_x), m_y(_y) {}

Vector2f::Vector2f()
{
    m_x = 0;
    m_y = 0;
}

float Vector2f::GetX()
{
    return m_x;
}

float Vector2f::GetY()
{
    return m_y;
}

void Vector2f::SetX(float _x)
{
    m_x = _x;
}

void Vector2f::SetY(float _y)
{
    m_y = _y;
}

void Vector2f::SetValue(float _x, float _y)
{
    m_x = _x;
    m_y = _y;
}

Vector2f Vector2f::Normalize()
{
    float d = Length();

    if (d == 0)
    {
        return Vector2f(0, 0);
    }

    float x = m_x / d;
    float y = m_y / d;

    return Vector2f(x, y);
}

float Vector2f::Length() const
{
    return std::sqrt(m_x * m_x + m_y * m_y);
}

float Vector2f::Dot(const Vector2f& other) const
{
    return m_x * other.m_x + m_y * other.m_y;
}

Vector2f Vector2f::operator+(const Vector2f& right)
{
    return Vector2f(m_x + right.m_x, m_y + right.m_y);
}

Vector2f Vector2f::operator-(const Vector2f& right)
{
    return Vector2f(m_x - right.m_x, m_y - right.m_y);
}

Vector2f Vector2f::operator*(float right)
{
    return Vector2f(m_x * right, m_y * right);
}

Vector2f Vector2f::operator/(float right)
{
    return Vector2f(m_x / right, m_y / right);
}

