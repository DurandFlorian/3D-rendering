#include "Ray3D.hpp"
#include <GL/freeglut.h>

Ray3D::Ray3D(Point3D &A, Point3D &B, Color color)
    : _A{A}, _B{B}, _color{color}
{
}

Ray3D::Ray3D(const Ray3D &ray) : Ray3D(ray._A, ray._B, ray._color)
{
}

const Point3D &Ray3D::get_A() const
{
    return _A;
}

const Point3D &Ray3D::get_B() const
{
    return _B;
}

const Ray3D &Ray3D::operator=(const Ray3D &ray)
{
    _A = ray._A;
    _B = ray._B;
    return *this;
}

void Ray3D::set_color(const Color &color)
{
    _color = color;
}

const Color &Ray3D::get_color() const
{
    return _color;
}