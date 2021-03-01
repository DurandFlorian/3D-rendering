#pragma once
#include "Vector2D.hpp"
#include "Matrix2D.hpp"
#include <math.h>

#define SQRT2 sqrt(2)
#define CANONICAL_CENTER \
    Point2D { 0, 0 }

class Ray2D;

class Shape2D
{
public:
    virtual void draw() = 0;

    Shape2D()
    {
    }

    virtual ~Shape2D()
    {
    }

    void rotate(double theta)
    {
        _Md = Matrix2D::rotation(theta) * _Md;
        _Mi = _Mi * Matrix2D::rotation(-theta);
        _Mn = Matrix2D::rotation(theta) * _Mn;
    }

    void translate(double x, double y)
    {
        _Md = Matrix2D::translation(x, y) * _Md;
        _Mi = _Mi * Matrix2D::translation(-x, -y);
    }

    void deform(double a, double b)
    {
        _Md = Matrix2D::homothety(a, b) * _Md;
        _Mi = _Mi * Matrix2D::homothety(1 / a, 1 / b);
        _Mn = Matrix2D::homothety(b, a) * _Mn;
    }

    virtual bool intersect(const Ray2D ray, Point2D &P, Vector2D &N) = 0;

protected:
    Matrix2D _Md;
    Matrix2D _Mi;
    Matrix2D _Mn;
};