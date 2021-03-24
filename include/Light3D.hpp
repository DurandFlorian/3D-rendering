#pragma once

#include "Color.hpp"

class Light3D
{
public:
    Light3D(Point3D position, Color color, double ambi) : _position{position}, _color{color}, _ambi{ambi}
    {
    }

    const Color &color()
    {
        return _color;
    }

    double ambi()
    {
        return _ambi;
    }

    const Point3D &position()
    {
        return _position;
    }

private:
    Point3D _position;
    Color _color;
    double _ambi;
};