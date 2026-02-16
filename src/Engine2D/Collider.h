#pragma once
#include "Component.h"
#include "Lib2D/Drawable.h"

enum ColliderType
{
    Rectangle,
    Circle
};

class Collider : public Component, public Drawable
{
protected:
    float m_offsetX;
    float m_offsetY;
    ColliderType m_type;

    bool m_isActived;
    bool m_isVisible;

public:
    Collider(ColliderType type);
    virtual ~Collider() {}

    ColliderType GetType() const { return m_type; }

    void SetOffset(float _ox, float _oy);

    void SetActive(bool _value) { m_isActived = _value; }
    bool IsActived() { return m_isActived; }

    void SetVisible(bool _value) { m_isVisible = _value; }
    bool IsVisible() { return m_isVisible; }

    virtual bool IsColliding(Collider* other) = 0;

    virtual float GetLeft() = 0;
    virtual float GetRight() = 0;
    virtual float GetTop() = 0;
    virtual float GetBottom() = 0;
};
