#pragma once
#include <cmath>
class Vector2D
{
public:
	float x;
	float y;
	float mag;
public:
	Vector2D() { x = 0; y = 0; mag = 0; };
	Vector2D(const float x, const float y);
	Vector2D(const POINT& _pt);
	Vector2D normalize();
	Vector2D operator+(const Vector2D&);
	Vector2D operator/(float t);
	Vector2D operator=(POINT _pt);
	Vector2D operator*(int _i);
	void operator+=(Vector2D _vOther);
	bool operator==(const Vector2D&);

	friend Vector2D operator*(float t, Vector2D& v);

};