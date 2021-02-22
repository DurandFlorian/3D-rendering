#pragma once

#include "Point2D.hpp"
#include "Vector2D.hpp"

#define SQRT2 sqrt(2)
#define CANONICAL_CENTER Point2D{0,0}

class Ray2D
{
public:

    Ray2D(Point2D& A, Point2D& B);

    Ray2D();
    
   
    bool intersect_canocical_circle(Point2D &intersection_point,Vector2D& N);

    bool intersect_canocical_square(Point2D &intersection_point,Vector2D& N);

    bool projection(const Point2D &point, Point2D &intersection_point);

    Point2D& get_A();

    Point2D& get_B();

    void draw();

private:
    Point2D* _A;
    Point2D* _B;
};