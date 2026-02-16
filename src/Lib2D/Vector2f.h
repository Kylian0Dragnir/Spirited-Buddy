#pragma once

class Vector2f
{
private:

	float m_x;
	float m_y;

public:

	Vector2f(float _x, float _y);
	Vector2f();
	float GetX();
	float GetY();
	void SetX(float _x);
	void SetY(float _y);
	void SetValue(float _x, float _y);
	Vector2f Normalize();

	float Length() const;
	float Dot(const Vector2f& other) const;

	Vector2f operator+(const Vector2f& right);
	Vector2f operator-(const Vector2f& right);
	Vector2f operator*(float right);
	Vector2f operator/(float right);
};

