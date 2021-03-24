#include "Circle2D.hpp"
#include "Ray2D.hpp"
#include <GL/freeglut.h>
#include <math.h>

Circle2D::Circle2D(Color color) : Shape2D(color)
{
}

void Circle2D::draw() const
{
    _color.set_color();
    int triangle_amount = 100;
    GLdouble two_pi = 2.0 * PI;
    Point2D C{CANONICAL_CENTER._x, CANONICAL_CENTER._y};
    C = _Md * C;
    C.draw();
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= triangle_amount; i++)
    {
        Point2D P{CANONICAL_CENTER._x + (1 * cos(i * two_pi / triangle_amount)),
                  CANONICAL_CENTER._y + (1 * sin(i * two_pi / triangle_amount))};
        P = _Md * P;
        P.draw();
    }
    glEnd();
}

bool Circle2D::intersect(Ray2D &ray, Point2D &P, Vector2D &N) const
{
    Point2D A = _Mi * ray.get_A();
    Point2D B = _Mi * ray.get_B();
    Vector2D opposite_vector = Vector2D::vector_from_points(A, CANONICAL_CENTER);
    Vector2D normalized_vector = Vector2D::vector_from_points(A, B).normalize();
    double t = normalized_vector.dot_product(opposite_vector);
    if (t < 0.)
    {
        return false;
    }
    Point2D T = A + t * normalized_vector;
    double d = CANONICAL_CENTER.sqrtDistance(T);
    if (d > 1.)
    {
        return false;
    }
    double e = t - sqrt(1. - d);
    P = A + e * normalized_vector;
    N = Vector2D::vector_from_points(CANONICAL_CENTER, P).normalize();
    P = _Md * P;
    return true;
}