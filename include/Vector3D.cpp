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
    return Vector3D{B.x() - A.x(), B.y() - A.y(), B.z() - A.z()};
}

Vector3D &Vector3D::normalize()
{
    double norm = (*this).dot_product(*this);
    if (norm < 1e-8)
    {
        return *this;
    }
    norm = 1. / sqrt(norm);
    x() *= norm;
    y() *= norm;
    z() *= norm;
    return *this;
}

Vector3D::~Vector3D()
{
}

Vector3D Vector3D::cross_product(const Vector3D &v) const
{
    return Vector3D{
        y() * v.z() - z() * v.y(),
        x() * v.z() - z() * v.x(),
        x() * v.y() - y() * v.z()};
}

double Vector3D::dot_product(const Vector3D &v) const
{
    return x() * v.x() + y() * v.y() + z() * v.z();
}

Vector3D operator/(const Vector3D &u, const Vector3D &v)
{
    return Vector3D{u.x() / v.x(), u.y() / v.y(), u.z() / v.z()};
}

Vector3D Vector3D::operator-() const
{
    Vector3D v;
    v.x() = -x();
    v.y() = -y();
    v.z() = -z();
    return v;
}

Vector3D operator*(double d, const Vector3D &v)
{
    Vector3D u;
    u.x() = d * v.x();
    u.y() = d * v.y();
    u.z() = d * v.z();
    return u;
}

Vector3D operator-(const Vector3D &u, const Vector3D &v)
{
    return Vector3D{u.x() - v.x(), u.y() - v.y(), u.z() - v.z()};
}

Vector3D operator+(const Vector3D &u, const Vector3D &v)
{
    return Vector3D{u.x() + v.x(), u.y() + v.y(), u.z() + v.z()};
}

Vector3D Vector3D::VctTransmitted(const Vector3D &u, const Vector3D &N, double sigma)
{
    auto ps = N.dot_product(u);
    return (sqrt(1. - sigma * sigma * (1. - ps * ps)) - sigma * ps) * N + sigma * u;
}