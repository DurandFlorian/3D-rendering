#pragma once

#include "Ray2D.hpp"
#include "Shape2D.hpp"
#include <vector>

class Camera2D
{
public:
    Camera2D(Ray2D, double);

    Camera2D();

    void trace_rays(std::vector<Shape2D*> objects);

    const Camera2D& operator=(const Camera2D&);

private:
    Ray2D _focal;
    double _size;
    const double _RAYS = 100;
};
