#pragma once

#include "Shape3D.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"

class Ray3D : public Shape3D
{
public:
    Ray3D(Point3D &, Point3D &, Color);

    Ray3D(const Ray3D &);
    
    bool intersect(Ray3D &ray, Point3D &P, Vector3D &N) const override;

    const Point3D &get_A() const;

    const Point3D &get_B() const;

    const Ray3D &operator=(const Ray3D &);

    void set_color(const Color &color);

private:
    Point3D &_A;
    Point3D &_B;
};