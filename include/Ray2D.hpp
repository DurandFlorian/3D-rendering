#pragma once

#include "Shape2D.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"

class Ray2D : public Shape2D
{
public:

    Ray2D(Point2D& A, Point2D& B);

    Ray2D();
    
    bool intersect(const Ray2D ray,Point2D& P,Vector2D& N);

    /*
    bool intersect_canocical_circle(Point2D &intersection_point,Vector2D& N);

    bool intersect_canocical_square(Point2D &intersection_point,Vector2D& N);

    bool projection(const Point2D &point, Point2D &intersection_point);
    */

    Point2D& get_A() const;

    Point2D& get_B() const;

    void draw();

private:
    Point2D* _A;
    Point2D* _B;
};