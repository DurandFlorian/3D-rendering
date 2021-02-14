#include "Circle2D.hpp"
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