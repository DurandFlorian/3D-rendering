#include "Circle2D.hpp"
#include "Ray2D.hpp"
#include <GL/freeglut.h>
#include <math.h>

Circle2D::Circle2D(Point2D &center, double radius)
    : _center{&center}, _radius{radius}
{
}

Circle2D::Circle2D()
{
}

const Point2D &Circle2D::center() const
{
    return *_center;
}

double Circle2D::diameter() const
{
    return _radius * _radius;
}

void Circle2D::draw_filled()
{
    int triangle_amount = 20;
    GLdouble two_pi = 2.0 * PI;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(_center->_x, _center->_y);
    for (int i = 0; i <= triangle_amount; i++)
    {
        glVertex2f(
            _center->_x + (_radius * cos(i * two_pi / triangle_amount)),
            _center->_y + (_radius * sin(i * two_pi / triangle_amount)));
    }
    glEnd();
}

void Circle2D::draw()
{
    int line_amount = 100;
    GLdouble two_pi = 2.0 * PI;
    glVertex2f(_center->_x, _center->_y);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= line_amount; i++)
    {
        glVertex2f(
            _center->_x + (_radius * cos(i * two_pi / line_amount)),
            _center->_y + (_radius * sin(i * two_pi / line_amount)));
    }
    glEnd();
}

bool Circle2D::intersect(const Ray2D ray,Point2D& P,Vector2D& N){
    Vector2D opposite_vector = Vector2D::vector_from_points(ray.get_A(), CANONICAL_CENTER);
    Vector2D normalized_vector = Vector2D::vector_from_points(ray.get_A(), ray.get_B());
    normalized_vector.normalize();
    double t = normalized_vector.dot_product(opposite_vector);
    if (t < 0.)
    {
        return false;
    }
    Point2D T = ray.get_A() + t * normalized_vector;
    double d = CANONICAL_CENTER.sqrtDistance(T);
    if (d > 1.)
    {
        return false;
    }
    double e = t - sqrt(1. - d);
    P = ray.get_A() + e * normalized_vector;
    N = Vector2D::vector_from_points(CANONICAL_CENTER,P);
    N.normalize();
    return true;
}