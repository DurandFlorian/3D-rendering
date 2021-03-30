#include "Vector3D.hpp"
#include <math.h>

Vector3D::Vector3D(double x, double y, double z)
    : Point3D{x, y, z}
{
}

Vector3D::Vector3D()
{
}

Vector3D Vector3D::vector_from_points(const Point3D &A, const Point3D &B)
{
    return Vector3D{B._x - A._x, B._y - A._y, B._z - A._z};
}

Vector3D &Vector3D::normalize()
{
    double norm = (*this).dot_product(*this);
    if (norm < 1e-8)
    {
        return *this;
    }
    norm = 1. / sqrt(norm);
    _x *= norm;
    _y *= norm;
    _z *= norm;
    return *this;
}

Vector3D::~Vector3D()
{
}

Vector3D Vector3D::cross_product(const Vector3D &v) const
{
    return Vector3D{
        _y * v._z - _z * v._y,
        _x * v._z - _z * v._x,
        _x * v._y - _y * v._z};
}

double Vector3D::dot_product(const Vector3D &v) const
{
    return _x * v._x + _y * v._y + _z * v._z;
}

Vector3D operator/(const Vector3D &u, const Vector3D &v)
{
    return Vector3D{u._x / v._x, u._y / v._y, u._z / v._z};
}

Vector3D Vector3D::operator-() const
{
    Vector3D v;
    v._x = -_x;
    v._y = -_y;
    v._z = -_z;
    return v;
}

Vector3D operator*(double d, const Vector3D &v)
{
    Vector3D u;
    u._x = d * v._x;
    u._y = d * v._y;
    u._z = d * v._z;
    return u;
}

Vector3D operator-(const Vector3D &u, const Vector3D &v)
{
    return Vector3D{u._x - v._x, u._y - v._y, u._z - v._z};
}

Vector3D operator+(const Vector3D &u, const Vector3D &v)
{
    return Vector3D{u._x + v._x, u._y + v._y, u._z + v._z};
}

Vector3D Vector3D::VctTransmitted(const Vector3D &u, const Vector3D &N, double sigma)
{
    auto ps = N.dot_product(u);
    return (sqrt(1. - sigma * sigma * (1. - ps * ps)) - sigma * ps) * N + sigma * u;
}