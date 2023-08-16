#include "pch.h"
#include "Vector2D.h"

Vector2D::Vector2D(const float x, const float y)
{
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D(const POINT& _pt)
{
    x = (float)_pt.x;
    y = (float)_pt.y;
}

void Vector2D::normalize()
{
    float m = mag();
    x = x / m;
    y = y / m;
}

Vector2D Vector2D::operator+(const Vector2D& v)
{
    return Vector2D(x + v.x, y + v.y);
}

Vector2D operator*(float t, Vector2D& v)
{
    return Vector2D(v.x * t, v.y * t);
}

Vector2D Vector2D::operator/(float t)
{
    assert(!(0.f == t));
    return Vector2D(x / t, y / t);
}

Vector2D Vector2D::operator=(POINT _pt)
{
    return Vector2D(float(_pt.x), float(_pt.y));
}

Vector2D Vector2D::operator*(int _i)
{
    return Vector2D(x * (float)_i, y*(float)_i);
}

Vector2D Vector2D::operator*(float _f)
{
    return Vector2D(x * _f, y * _f);
}

void Vector2D::operator+=(Vector2D _vOther)
{
    x += _vOther.x;
    y += _vOther.y;
}

bool Vector2D::operator==(const Vector2D& v)
{

    return x == v.x && y == v.y;
}
