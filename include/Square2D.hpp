#pragma once

#include "Point2D.hpp"
#include "Shape2D.hpp"

class Square2D : public Shape2D
{

public:
    Square2D(Point2D center, double size);

    void draw();

private:
    Point2D _center;
    double _size;
};