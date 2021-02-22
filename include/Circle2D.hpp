#pragma once

#include "Point2D.hpp"

#include "Shape2D.hpp"
#include "Ray2D.hpp"

#define PI  3.14159265358979311599796346854

class Circle2D : public Shape2D
{
public :
    Circle2D(Point2D& center, double radius);

    Circle2D();

    const Point2D& center() const;

    double diameter() const;

    void draw_filled();

    void draw();

    bool intersect(Ray2D ray,Point2D& P,Vector2D& N);

private :
    Point2D* _center;
    double _radius;
};