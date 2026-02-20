#pragma once
#include "SDL.h"
#include "Vector2f.h"

typedef enum Flip
{
	FLIP_NONE = 0x00000000,
	FLIP_HORIZONTAL = 0x00000001,
	FLIP_VERTICAL = 0x00000002

} Flip;

class Transformable
{
protected:

	Vector2f m_pos;
	Vector2f m_rotationCenter;

	Flip m_flip;
	float m_angle;
	Vector2f m_scale;

public:

	Transformable(Vector2f _pos);

	Vector2f GetPos();
	void SetPos(Vector2f _pos);

	void SetScale(Vector2f _scale);
	Vector2f GetScale();

	void SetFlip(Flip _flip);
	Flip GetFlip();

	void SetRotation(float _angle);
	float GetAngle();

	void SetRotationCenter(int _x, int _y);
	void SetRotationCenter(Vector2f _vect);
	Vector2f GetRotationCenter();

	void Translate(float _dx, float _dy);
	void ResetTansform();
};

