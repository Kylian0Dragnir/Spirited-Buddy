#pragma once
#include "Component.h"
#include "Lib2D/Drawable.h"
#include "Lib2D/Vector2f.h"
#include <string>

enum ColliderType
{
    Rectangle,
    Circle
};

enum CollisionLayer
{
    NONE = 0,
    PLAYER_LAYER = 1 << 0,
    SPIRIT_LAYER = 1 << 1,
    ENV_LAYER = 1 << 2
};

class Collider : public Component, public Drawable
{
protected:
    float m_offsetX;
    float m_offsetY;
    ColliderType m_type;

    bool m_isActived;
    bool m_isVisible;
    bool m_isTrigger;

    CollisionLayer m_layer;
    uint32_t m_mask;

public:
    Collider(ColliderType _type, CollisionLayer layer, uint32_t _mask);
    virtual ~Collider() {}

    ColliderType GetType() const { return m_type; }

    CollisionLayer GetLayer() { return m_layer; }
    bool CanCollide(Collider* _other);

    void SetOffset(float _ox, float _oy);
    Vector2f GetOffset() { Vector2f offset(m_offsetX, m_offsetY); return offset; }

    void SetActive(bool _value) { m_isActived = _value; }
    bool IsActived() { return m_isActived; }

    void SetVisible(bool _value) { m_isVisible = _value; }
    bool IsVisible() { return m_isVisible; }

    void SetTrigger(bool _value) { m_isTrigger = _value; }
    bool IsTrigger() { return m_isTrigger; }

    uint32_t GetMask() { return m_mask; }

    virtual bool IsColliding(Collider* other) = 0;

    virtual float GetLeft() = 0;
    virtual float GetRight() = 0;
    virtual float GetTop() = 0;
    virtual float GetBottom() = 0;
};
