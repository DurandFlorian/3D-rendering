#include "Square2D.hpp"
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
