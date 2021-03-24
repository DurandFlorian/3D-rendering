#pragma once

#include "Shape3D.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"

class Ray3D
{
public:
    Ray3D(Point3D &, Point3D &, Color);

    Ray3D(const Ray3D &);

    const Point3D &get_A() const;

    const Point3D &get_B() const;

    const Ray3D &operator=(const Ray3D &);

    void set_color(const Color &color);

    const Color & get_color() const;

private:
    Point3D &_A;
    Point3D &_B;
    Color _color;
};