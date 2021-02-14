#include "Ray2D.hpp"
#include <math.h>
#include <GL/freeglut.h>

Ray2D::Ray2D(Point2D &A, Point2D &B)
    : _A{&A}, _B{&B}
{
}

Ray2D::Ray2D()
{
}

bool Ray2D::intersect(const Ray2D &ray, Point2D &intersection_point)
{
    Vector2D AB = Vector2D::vector_from_points(*_A, *_B);
    Vector2D CD = Vector2D::vector_from_points(*(ray._A), *(ray._B));
    double v = AB.cross_product(CD);
    if (fabs(v) < 1e-8) //parallèles
    {
        return false;
    }
    Vector2D opposite_vector = Vector2D::vector_from_points(*_A, *(ray._A));
    double t1 = opposite_vector.cross_product(CD) / v;
    if (t1 < 0. || t1 > 1.)
    {
        return false;
    }
    double t2 = opposite_vector.cross_product(AB) / v;
    if (t2 < 0. || t2 > 1.)
    {
        return false;
    }
    intersection_point = *_A + t1 * AB;
    return true;
}

bool Ray2D::intersect(const Circle2D &circle, Point2D &intersection_point)
{
    Vector2D opposite_vector = Vector2D::vector_from_points(*_A, circle.center());

    Vector2D normalized_vector = Vector2D::vector_from_points(*_A, *_B);
    normalized_vector.normalize();
    double t = normalized_vector.dot_product(opposite_vector);
    if (t < 0.)
    {
        return false;
    }
    Point2D T = *_A + t * normalized_vector;
    double d = circle.center().sqrtDistance(T);
    double diameter = circle.diameter();
    if (d > diameter)
    {
        return false;
    }
    double e = t - sqrt(diameter - d);
    intersection_point = *_A + e * normalized_vector;
    return true;
}

bool Ray2D::intersect_canocical_circle(Point2D &intersection_point)
{
    Vector2D opposite_vector = Vector2D::vector_from_points(*_A, CANONICAL_CENTER);
    Vector2D normalized_vector = Vector2D::vector_from_points(*_A, *_B);
    normalized_vector.normalize();
    double t = normalized_vector.dot_product(opposite_vector);
    if (t < 0.)
    {
        return false;
    }
    Point2D T = *_A + t * normalized_vector;
    double d = CANONICAL_CENTER.sqrtDistance(T);
    if (d > 1.)
    {
        return false;
    }
    double e = t - sqrt(1. - d);
    intersection_point = *_A + e * normalized_vector;
    return true;
}

bool Ray2D::intersect_canocical_square(Point2D &intersection_point)
{
    Vector2D normalized_vector = Vector2D::vector_from_points(*_A, *_B);
    normalized_vector.normalize();
    static bool flag[4] = {false, false, false, false};
    static Vector2D square_sides[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    flag[0] = _A->_x > 1;
    flag[1] = _A->_x < -1;
    flag[2] = _A->_y > 1;
    flag[3] = _A->_y < -1;
    for (int i = 0; i < 4; i++)
    {
        if (!flag[i])
        {
            continue;
        }
        double ps1 = Vector2D::vector_from_points(*_A, square_sides[i]).dot_product(square_sides[i]);
        if (ps1 >= 0.)
        {
            continue;
        }
        double ps2 = normalized_vector.dot_product(square_sides[i]);
        if (ps2 >= 0.)
        {
            continue;
        }
        double t = ps1 / ps2;
        intersection_point = *_A + t * normalized_vector;
        if (CANONICAL_CENTER.distance(intersection_point) > SQRT2)
        {
            continue;
        }
        return true;
    }
    return false;
}

bool Ray2D::projection(const Point2D &point, Point2D &intersection_point)
{
    Vector2D opposite_vector = Vector2D::vector_from_points(*_A, point);
    Vector2D AB = Vector2D::vector_from_points(*_A, *_B);
    double d = AB.dot_product(AB);
    if (fabs(d) < 1e-8)
    {
        return false;
    }
    double t = AB.dot_product(opposite_vector) / d;
    if (t < 0. || t > 1.)
    {
        return false;
    }
    intersection_point = *_A + t * AB;
    return true;
}

void Ray2D::draw()
{
    glBegin(GL_LINE_LOOP);
    glVertex2d(_A->_x, _A->_y);
    glVertex2d(_B->_x, _B->_y);
    glEnd();
}