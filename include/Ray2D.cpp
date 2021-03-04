#include "Ray2D.hpp"
#include <GL/freeglut.h>

Ray2D::Ray2D(Point2D &A, Point2D &B, Color color)
    : Shape2D(color), _A{A}, _B{B}
{
}

Ray2D::Ray2D(const Ray2D &ray) : Ray2D(ray._A, ray._B, ray._color)
{
}

bool Ray2D::intersect(Ray2D &ray, Point2D &P, Vector2D &N) const
{
    Vector2D AB = Vector2D::vector_from_points(_A, _B);
    Vector2D CD = Vector2D::vector_from_points(ray._A, ray._B);
    Vector2D AC = Vector2D::vector_from_points(_A, ray._A);
    double v = AB.cross_product(CD);
    if (fabs(v) < 1e-8)
    {
        return false;
    }
    double t = AC.cross_product(CD) / v;
    if (t < 0.)
    {
        return false;
    }
    double t2 = AC.cross_product(AB) / v;
    if (t2 < 0.)
    {
        return false;
    }
    P = _A + t * AB;
    N = Vector2D::vector_from_points(ray._A, P).normalize();
    return true;
}

const Point2D &Ray2D::get_A() const
{
    return _A;
}

const Point2D &Ray2D::get_B() const
{
    return _B;
}

void Ray2D::draw() const
{
    _color.set_color();
    glBegin(GL_LINE_LOOP);
    _A.draw();
    _B.draw();
    glEnd();
}

const Ray2D &Ray2D::operator=(const Ray2D &ray)
{
    _A = ray._A;
    _B = ray._B;
    return *this;
}

void Ray2D::set_color(const Color& color)
{
    _color = color;
}