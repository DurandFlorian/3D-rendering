#include "Vector2D.hpp"
#include <math.h>

Vector2D::Vector2D(double x, double y)
    : Point2D{x, y}
{
}

Vector2D::Vector2D()
{
}

Vector2D Vector2D::vector_from_points(const Point2D &A, const Point2D &B)
{
    return Vector2D{B._x - A._x, B._y - A._y};
}

const Vector2D &Vector2D::normalize()
{
    double norm = _x * _x + _y * _y;
    if (norm < 1e-8)
    {
        norm = 1.;
    }
    else
    {
        norm = 1. / sqrt(norm);
    }
    _x *= norm;
    _y *= norm;
    return *this;
}

Vector2D::~Vector2D()
{
}

double Vector2D::cross_product(const Vector2D &v) const
{
    return _x * v._y - _y * v._x;
}

double Vector2D::dot_product(const Vector2D &v) const
{
    return _x * v._x + _y * v._y;
}

Vector2D Vector2D::perpendicular() const
{
    return Vector2D{_y, -_x};
}