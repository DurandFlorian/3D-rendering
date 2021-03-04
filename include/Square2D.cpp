#include "Square2D.hpp"
#include "Ray2D.hpp"
#include <GL/freeglut.h>

Square2D::Square2D(Color color) : Shape2D(color)
{
}

void Square2D::draw() const
{
    _color.set_color();
    Point2D p1{1, 1};
    Point2D p2{1, -1};
    Point2D p3{-1, -1};
    Point2D p4{-1, 1};
    p1 = _Md * p1;
    p2 = _Md * p2;
    p3 = _Md * p3;
    p4 = _Md * p4;
    glBegin(GL_QUADS);
    p1.draw();
    p2.draw();
    p3.draw();
    p4.draw();
    glEnd();
}

bool Square2D::intersect(Ray2D& ray, Point2D &P, Vector2D &N) const
{
    Point2D A = _Mi * ray.get_A();
    Point2D B = _Mi * ray.get_B();
    Vector2D AB = Vector2D::vector_from_points(A, B).normalize();
    bool flag[4] = {false, false, false, false};
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