#include "Point2D.hpp"
#include "Circle2D.hpp"
#include <GL/freeglut.h>
#include <math.h>

Point2D::Point2D(double x, double y)
    : _x{x}, _y{y}
{
}

Point2D::Point2D(const Point2D &p)
    : _x{p._x}, _y{p._y}
{
}

Point2D::Point2D()
{
}

void Point2D::draw() const
{
    glVertex2d(_x, _y);
}

double Point2D::distance(const Point2D &B) const
{
    return sqrt(pow(B._x - _x, 2) + pow(B._y - _y, 2));
}

double Point2D::sqrtDistance(const Point2D &B) const
{
    return pow(B._x - _x, 2) + pow(B._y - _y, 2);
}

std::ostream &operator<<(std::ostream &os, const Point2D &p)
{
    os << p._x << " " << p._y << std::endl;
    return os;
}

Point2D operator+(const Point2D &u, const Point2D &v)
{
    return Point2D{u._x + v._x, u._y + v._y};
}

Point2D operator-(const Point2D &u, const Point2D &v)
{
    return Point2D{u._x - v._x, u._y - v._y};
}

Point2D operator/(const Point2D &u, const double t)
{
    return Point2D{u._x / t, u._y / t};
}

Point2D operator*(const double t, const Point2D &u)
{
    return Point2D{t * u._x, t * u._y};
}

Point2D operator*(const Point2D &u, const double t)
{
    return Point2D{t * u._x, t * u._y};
}

const Point2D &Point2D::operator=(const Point2D &p)
{
    _x = p._x;
    _y = p._y;
    return *this;
}

Point2D::~Point2D()
{
}