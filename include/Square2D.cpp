#include "Square2D.hpp"
#include "Ray2D.hpp"
#include <GL/freeglut.h>

Square2D::Square2D(Point2D center, double size)
    : _center{center}, _size{size}
{
}

void Square2D::draw()
{
    double half_size = _size / 2;
    glBegin(GL_LINE_LOOP);
    glVertex2f(_center._x - half_size, _center._y - half_size);
    glVertex2f(_center._x - half_size, _center._y + half_size);
    glVertex2f(_center._x + half_size, _center._y + half_size);
    glVertex2f(_center._x + half_size, _center._y - half_size);
    glEnd();
}

bool Square2D::intersect(const Ray2D ray, Point2D &P, Vector2D &N)
{
    Point2D A = ray.get_A();
    Point2D B = ray.get_B();
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
        N = square_sides[i];
        if (CANONICAL_CENTER.distance(P) > SQRT2)
        {
            continue;
        }
        return true;
    }
    return false;
}
