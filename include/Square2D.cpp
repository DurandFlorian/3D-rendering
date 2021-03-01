#include "Square2D.hpp"
#include "Ray2D.hpp"
#include <GL/freeglut.h>

void Square2D::draw()
{
    Point2D p1{1, 1};
    Point2D p2{1, -1};
    Point2D p3{-1, -1};
    Point2D p4{-1, 1};
    p1 = _Md * p1;
    p2 = _Md * p2;
    p3 = _Md * p3;
    p4 = _Md * p4;
    glBegin(GL_LINE_LOOP);
    glVertex2f(p1._x, p1._y);
    glVertex2f(p2._x, p2._y);
    glVertex2f(p3._x, p3._y);
    glVertex2f(p4._x, p4._y);
    glEnd();
}

bool Square2D::intersect(const Ray2D ray, Point2D &P, Vector2D &N)
{
    Point2D A = _Mi * ray.get_A();
    Point2D B = _Mi * ray.get_B();
    Vector2D AB = Vector2D::vector_from_points(A, B);
    AB.normalize();
    static bool flag[4] = {false, false, false, false};
    static Vector2D square_sides[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    flag[0] = A._x > 1;
    flag[1] = A._x < -1;
    flag[2] = A._y > 1;
    flag[3] = A._y < -1;
    for (int i = 0; i < 4; i++)
    {
        if (!flag[i])
        {
            continue;
        }
        double ps1 = Vector2D::vector_from_points(A, square_sides[i]).dot_product(square_sides[i]);
        if (ps1 >= 0.)
        {
            continue;
        }
        double ps2 = AB.dot_product(square_sides[i]);
        if (ps2 >= 0.)
        {
            continue;
        }
        double t = ps1 / ps2;
        P = A + t * AB;
        if (CANONICAL_CENTER.distance(P) > SQRT2)
        {
            continue;
        }
        N = square_sides[i];
        P = _Md * P;
        return true;
    }
    return false;
}