#pragma once
#include <cmath>
class Vector2D
{
public:
	float x;
	float y;
public:
	Vector2D() { x = 0; y = 0;};
	Vector2D(const float x, const float y);
	Vector2D(const POINT& _pt);
public:
	float mag(){return (float)sqrt(pow(x, 2) + pow(y, 2));}
	void normalize();
	Vector2D operator+(const Vector2D&);
	Vector2D operator+(float _f) { return Vector2D(x += _f, y += _f); }
	Vector2D operator/(float t);
	Vector2D operator=(POINT _pt);
	Vector2D operator*(int _i);
	Vector2D operator*(float _f);
	void operator*=(float _f) { x *= _f, y *= _f; }
	void operator+=(Vector2D _vOther);
	void operator+=(float _f) { x += _f, y += _f; }
	bool operator==(const Vector2D&);

	friend Vector2D operator*(float t, Vector2D& v);

};