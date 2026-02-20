#include "Transformable.h"

Transformable::Transformable(Vector2f _pos) : m_pos(_pos)
{
	m_flip = FLIP_NONE;
	m_angle = 0.f;
	m_rotationCenter = { -1, -1 };
	m_scale = {1,1};
}

Vector2f Transformable::GetPos()
{
	return m_pos;
}

Vector2f Transformable::GetScale()
{
	return m_scale;
}

void Transformable::SetPos(Vector2f _pos)
{
	m_pos = _pos;
}

void Transformable::Translate(float _dx, float _dy)
{
	float dx = _dx + m_pos.GetX();
	float dy = _dy + m_pos.GetY();
	m_pos.SetValue(dx, dy);
}

void Transformable::SetFlip(Flip _flip)
{
	m_flip = _flip;
}

Flip Transformable::GetFlip()
{
	return m_flip;
}

void Transformable::SetRotation(float _angle)
{
	m_angle = _angle;
}

float Transformable::GetAngle()
{
	return m_angle;
}

void Transformable::SetRotationCenter(int _x, int _y)
{
	m_rotationCenter.SetValue(_x, _y);
}

void Transformable::SetRotationCenter(Vector2f _vect)
{
	m_rotationCenter = _vect;
}

Vector2f Transformable::GetRotationCenter()
{
	return m_rotationCenter;
}

void Transformable::SetScale(Vector2f _scale)
{
	m_scale = _scale;
}

void Transformable::ResetTansform()
{
	m_flip = FLIP_NONE;
	m_angle = 0.F;
	m_rotationCenter = { -1,-1 };
	m_scale = {1, 1};
}
