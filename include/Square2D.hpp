#pragma once

#include "Point2D.hpp"
#include "Shape2D.hpp"

class Square2D : public Shape2D
{

public:
    Square2D(Point2D center, double size);

    void draw();

    bool intersect(const Ray2D ray,Point2D& P,Vector2D& N) override;

private:
    Point2D _center;
    double _size;
};