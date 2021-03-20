#pragma once
#include "Vector2D.hpp"
#include "Matrix2D.hpp"
#include "Color.hpp"
#include <math.h>

#define SQRT2 sqrt(2)
#define CANONICAL_CENTER \
    Point2D { 0, 0 }

class Ray2D;

class Shape2D
{
public:
    virtual void draw() const = 0;

    Shape2D(Color color) : _color{color}
    {
    }

    virtual ~Shape2D()
    {
    }

    Shape2D &rotate(double theta)
    {
        _Md = Matrix2D::rotation(theta) * _Md;
        _Mi = _Mi * Matrix2D::rotation(-theta);
        _Mn = Matrix2D::rotation(theta) * _Mn;
        return *this;
    }

     Shape2D &translate(double x, double y)
    {
        _Md = Matrix2D::translation(x, y) * _Md;
        _Mi = _Mi * Matrix2D::translation(-x, -y);
        return *this;
    }

     Shape2D &deform(double a, double b)
    {
        _Md = Matrix2D::homothety(a, b) * _Md;
        _Mi = _Mi * Matrix2D::homothety(1 / a, 1 / b);
        _Mn = Matrix2D::homothety(b, a) * _Mn;
        return *this;
    }

    virtual bool intersect(Ray2D &ray, Point2D &P, Vector2D &N) const = 0;

    Color get_color() const
    {
        return _color;
    }

protected:
    Color _color;
    Matrix2D _Md;
    Matrix2D _Mi;
    Matrix2D _Mn;
};