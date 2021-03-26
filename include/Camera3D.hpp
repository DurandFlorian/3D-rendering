#pragma once

#include "Ray3D.hpp"
#include "Shape3D.hpp"
#include <vector>

class Camera3D
{
public:
    Camera3D(const Point3D &T, double alpha, double beta, double focal, double distance);

    void trace_rays(std::vector<Shape3D *> objects, std::vector<Light3D *> lights);

    const Camera3D &operator=(const Camera3D &);

    Camera3D &rotate_x(double alpha)
    {
        _Md = Matrix3D::rotation_x(alpha) * _Md;
        return *this;
    }

    Camera3D &rotate_y(double beta)
    {
        _Md = Matrix3D::rotation_y(beta) * _Md;
        return *this;
    }

    Camera3D &rotate_z(double gamma)
    {
        _Md = Matrix3D::rotation_z(gamma) * _Md;
        return *this;
    }

    Camera3D &translate(double x, double y, double z)
    {
        _Md = Matrix3D::translation(x, y, z) * _Md;
        return *this;
    }

    Camera3D &deform(double a, double b, double c)
    {
        _Md = Matrix3D::homothety(a, b, c) * _Md;
        return *this;
    }

private:
    Matrix3D _Md;
    static constexpr int _rows = 250;
    static constexpr int _cols = 250;
};
