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

    void rotate_x(double theta){
        _position = Matrix3D::rotation_x(theta) * _position;
    }

    void rotate_y(double theta){
        _position = Matrix3D::rotation_y(theta) * _position;
    }
    
    void rotate_z(double theta){
        _position = Matrix3D::rotation_z(theta) * _position;
    }

private:
    Point3D _position;
    Color _color;
    double _ambi;
};