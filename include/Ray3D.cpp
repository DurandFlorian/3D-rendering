#include "Ray3D.hpp"
#include <GL/freeglut.h>

Ray3D::Ray3D(Point3D &A, Point3D &B, Color color)
    : Shape3D(color), _A{A}, _B{B}
{
}

Ray3D::Ray3D(const Ray3D &ray) : Ray3D(ray._A, ray._B, ray._color)
{
}

bool Ray3D::intersect(Ray3D &ray, Point3D &P, Vector3D &N) const
{
    Vector3D AB = Vector3D::vector_from_points(_A, _B);
    Vector3D CD = Vector3D::vector_from_points(ray._A, ray._B);
    Vector3D AC = Vector3D::vector_from_points(_A, ray._A);
    Vector3D v = AB.cross_product(CD);
    if (fabs(v._x) < 1e-8 && fabs(v._y) < 1e-8 && fabs(v._z) < 1e-8)
    {
        return false;
    }
    Vector3D tv = AC.cross_product(CD) / v;
    double t = tv.dot_product(tv);
    if (t < 0.)
    {
        return false;
    }
    Vector3D t2v = AC.cross_product(AB) / v;
    double t2 = t2v.dot_product(t2v);
    if (t2 < 0.)
    {
        return false;
    }
    P = _A + t * AB;
    N = Vector3D::vector_from_points(ray._A, P).normalize();
    return true;
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