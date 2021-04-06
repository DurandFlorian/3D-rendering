#pragma once

#include <array>
#include "Point.hpp"
#include "Vector3D.hpp"

class Matrix3D
{
public:
    Matrix3D();

    Matrix3D(const Matrix3D &);

    Matrix3D operator*(const Matrix3D &);

    const Point3D operator*(const Point3D &) const;

    Vector3D operator*(const Vector3D &P) const;

    const Matrix3D &operator=(const Matrix3D &);

    static Matrix3D rotation(double theta);

    static Matrix3D rotation_x(double alpha);

    static Matrix3D rotation_y(double beta);

    static Matrix3D rotation_z(double gamma);

    static Matrix3D translation(double x, double y, double z);

    static Matrix3D homothety(double a, double b, double c);

private:
    static const int _rows = 4;
    static const int _cols = 4;
    std::array<double, 16> _matrix{
        1,
        0,
        0,
        0,
        0,
        1,
        0,
        0,
        0,
        0,
        1,
        0,
        0,
        0,
        0,
        1};
};