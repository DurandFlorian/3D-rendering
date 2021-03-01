#include "Circle2D.hpp"
#include "Ray2D.hpp"
#include <GL/freeglut.h>
#include <math.h>

void Circle2D::draw_filled()
{
    int triangle_amount = 20;
    GLdouble two_pi = 2.0 * PI;
    Point2D C{CANONICAL_CENTER._x, CANONICAL_CENTER._y};
    C = _Md * C;
    glVertex2f(C._x, C._y);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= triangle_amount; i++)
    {
        Point2D P{CANONICAL_CENTER._x + (1 * cos(i * two_pi / triangle_amount)),
                  CANONICAL_CENTER._y + (1 * sin(i * two_pi / triangle_amount))};
        P = _Md * P;
        glVertex2f(P._x, P._y);
    }
    glEnd();
}

void Circle2D::draw()
{
    int line_amount = 100;
    GLdouble two_pi = 2.0 * PI;
    Point2D C{CANONICAL_CENTER._x, CANONICAL_CENTER._y};
    C = _Md * C;
    glVertex2f(C._x, C._y);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= line_amount; i++)
    {
        Point2D P{CANONICAL_CENTER._x + (1 * cos(i * two_pi / line_amount)), CANONICAL_CENTER._y + (1 * sin(i * two_pi / line_amount))};
        P = _Md * P;
        glVertex2f(P._x, P._y);
    }
    glEnd();
}

bool Circle2D::intersect(const Ray2D ray, Point2D &P, Vector2D &N)
{
    Point2D A = _Mi * ray.get_A();
    Point2D B = _Mi * ray.get_B();
    Vector2D opposite_vector = Vector2D::vector_from_points(A, CANONICAL_CENTER);
    Vector2D normalized_vector = Vector2D::vector_from_points(A, B);
    normalized_vector.normalize();
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
    N = Vector2D::vector_from_points(CANONICAL_CENTER, P);
    N.normalize();
    P = _Md * P;
    return true;
}