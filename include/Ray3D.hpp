#pragma once

#include "Shape3D.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <vector>

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

    Color trace(std::vector<Shape3D *> objects, std::vector<Light3D> lights);

private:
    Point3D &_A;
    Point3D &_B;
    Color _color;
};