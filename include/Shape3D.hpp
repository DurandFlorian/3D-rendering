#pragma once

#include "Vector3D.hpp"
#include "Matrix3D.hpp"
#include "Color.hpp"
#include <math.h>

#define SQRT2 sqrt(2)
#define CANONICAL_CENTER \
    Point3D { 0, 0, 0 }

class Ray3D;

class Shape3D
{
public:
    Shape3D(Color color) : _color{color}
    {
    }

    virtual ~Shape3D()
    {
    }

    Shape3D &rotate_x(double alpha)
    {
        _Md = Matrix3D::rotation_x(alpha) * _Md;
        _Mi = _Mi * Matrix3D::rotation_x(-alpha);
        _Mn = Matrix3D::rotation_x(alpha) * _Mn;
        return *this;
    }

    Shape3D &rotate_y(double beta)
    {
        _Md = Matrix3D::rotation_y(beta) * _Md;
        _Mi = _Mi * Matrix3D::rotation_y(-beta);
        _Mn = Matrix3D::rotation_y(beta) * _Mn;
        return *this;
    }

    Shape3D &rotate_z(double gamma)
    {
        _Md = Matrix3D::rotation_z(gamma) * _Md;
        _Mi = _Mi * Matrix3D::rotation_z(-gamma);
        _Mn = Matrix3D::rotation_z(gamma) * _Mn;
        return *this;
    }

    Shape3D &translate(double x, double y, double z)
    {
        _Md = Matrix3D::translation(x, y, z) * _Md;
        _Mi = _Mi * Matrix3D::translation(-x, -y, -z);
        return *this;
    }

    Shape3D &deform(double a, double b, double c)
    {
        _Md = Matrix3D::homothety(a, b, c) * _Md;
        _Mi = _Mi * Matrix3D::homothety(1 / a, 1 / b, 1 / c);
        _Mn = Matrix3D::homothety(b * c, a * c, a * b) * _Mn;
        return *this;
    }

    virtual bool intersect(Ray3D &ray, Point3D &P, Vector3D &N) const = 0;

    Color get_color() const
    {
        return _color;
    }

protected:
    Color _color;
    Matrix3D _Md;
    Matrix3D _Mi;
    Matrix3D _Mn;
};