#pragma once

#include "Shape3D.hpp"
#include "Point.hpp"
#include "Vector3D.hpp"
#include <vector>

class Ray3D
{
public:
    Ray3D();

    Ray3D(Point3D &, Point3D &);

    Ray3D(Point3D &A, Vector3D v);

    Ray3D(const Ray3D &);

    const Point3D &get_A() const;

    const Point3D &get_B() const;

    const Ray3D &operator=(const Ray3D &);

    Color trace(std::vector<Shape3D *> objects, std::vector<Light3D *> lights, int rec);

private:
    Point3D _A;
    Point3D _B;
};