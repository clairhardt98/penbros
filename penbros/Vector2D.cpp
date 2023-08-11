#include "pch.h"
#include "Vector2D.h"

Vector2D::Vector2D(const float x, const float y)
{
    this->x = x;
    this->y = y;
    mag = (float)sqrt(pow(x, 2) + pow(y, 2));
}

Vector2D::Vector2D(const POINT& _pt)
{
    x = (float)_pt.x;
    y = (float)_pt.y;
    mag = (float)sqrt(pow(x, 2) + pow(y, 2));
}

Vector2D Vector2D::normalize()
{
    Vector2D norm;
    norm.x = x / mag;
    norm.y = y / mag;
    norm.mag = 1;
    return norm;
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

bool Vector2D::operator==(const Vector2D& v)
{

    return x == v.x && y == v.y;
}
