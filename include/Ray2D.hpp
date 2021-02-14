#pragma once

#include "Point2D.hpp"
#include "Vector2D.hpp"
#include "Circle2D.hpp"

#define SQRT2 sqrt(2)
#define CANONICAL_CENTER Point2D{0,0}

class Ray2D
{
public:

    Ray2D(Point2D& A, Point2D& B);

    Ray2D();
    
    bool intersect(const Ray2D &ray, Point2D &intersection_point);

    bool intersect(const Circle2D &circle, Point2D &intersection_point);

    bool intersect_canocical_circle(Point2D &intersection_point);

    bool intersect_canocical_square(Point2D &intersection_point);

    bool projection(const Point2D &point, Point2D &intersection_point);

    void draw();

private:
    Point2D* _A;
    Point2D* _B;
};