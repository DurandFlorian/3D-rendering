#include "Point3D.hpp"
#include <GL/freeglut.h>
#include <math.h>

Point3D::Point3D(double x, double y, double z)
    : _x{x}, _y{y}, _z{z}
{
}

Point3D::Point3D(const Point3D &p)
    : _x{p._x}, _y{p._y}, _z{p._z}
{
}

Point3D::Point3D()
{
}

double Point3D::distance(const Point3D &B) const
{
    return sqrt(pow(B._x - _x, 2) + pow(B._y - _y, 2) + pow(B._z - _z, 2));
}

double Point3D::sqrtDistance(const Point3D &B) const
{
    return pow(B._x - _x, 2) + pow(B._y - _y, 2) + pow(B._z - _z, 2);
}

std::ostream &operator<<(std::ostream &os, const Point3D &p)
{
    os << p._x << " " << p._y << " " << p._z << std::endl;
    return os;
}

Point3D operator+(const Point3D &u, const Point3D &v)
{
    return Point3D{u._x + v._x, u._y + v._y, u._z + v._z};
}

Point3D operator-(const Point3D &u, const Point3D &v)
{
    return Point3D{u._x - v._x, u._y - v._y, u._z - v._z};
}

Point3D operator/(const Point3D &u, const double t)
{
    return Point3D{u._x / t, u._y / t, u._z / t};
}

Point3D operator*(const double t, const Point3D &u)
{
    return Point3D{t * u._x, t * u._y, t * u._z};
}

Point3D operator*(const Point3D &u, const double t)
{
    return Point3D{t * u._x, t * u._y, t * u._z};
}

const Point3D &Point3D::operator=(const Point3D &p)
{
    _x = p._x;
    _y = p._y;
    _z = p._z;
    return *this;
}

Point3D::~Point3D()
{
}