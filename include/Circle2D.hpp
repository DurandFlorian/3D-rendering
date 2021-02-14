#pragma once

#include "Point2D.hpp"

#define PI  3.14159265358979311599796346854

class Circle2D
{
public :
    Circle2D(Point2D& center, double radius);

    Circle2D();

    const Point2D& center() const;

    double diameter() const;

    void draw_filled();

    void draw();

private :
    Point2D* _center;
    double _radius;
};