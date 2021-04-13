#pragma once

#include "Vector3D.hpp"
#include "Matrix3D.hpp"
#include "Color.hpp"
#include "Light3D.hpp"
#include <math.h>

#define CANONICAL_CENTER \
    Point3D { 0, 0, 0 }

class Ray3D;

class Shape3D
{
public:
    Shape3D(Color color, double diffusion, double spec, double shine, double alpha) : _color{color}, _diff{diffusion}, _spec{spec}, _shine{shine}, _alpha{alpha}
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

    virtual bool intersect(Ray3D &ray, Point3D &P, Vector3D &N, Ray3D &ray_out) const = 0;

    Color get_color(const Vector3D &N, const Vector3D &w, Light3D light, const Vector3D &u) const
    {
        Color color = light.ambi() * _color;
        if (_diff > 0.)
        {
            double t = N.dot_product(w);
            color += _diff * t * _color;
            if (_spec > 0. && _shine > 0.)
            {
                Vector3D wr = 2 * t * N - w;
                color += _spec * _shine * pow((-u).dot_product(wr), 1. / (1. - _shine)) * light.color();
            }
        }
        return color;
    }

    double get_spec()
    {
        return _spec;
    }

    double get_alpha()
    {
        return _alpha;
    }

protected:
    Color _color;
    Matrix3D _Md;
    Matrix3D _Mi;
    Matrix3D _Mn;
    double _diff;
    double _spec;
    double _shine;
    double _alpha;
    static constexpr double indice = 1.01;
};