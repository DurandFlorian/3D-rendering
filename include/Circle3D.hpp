#pragma once

#include "Point3D.hpp"
#include "Shape3D.hpp"
#include "Ray3D.hpp"
#include "Matrix3D.hpp"

#define PI 3.14159265358979311599796346854

class Circle3D : public Shape3D
{
public:
    Circle3D(Color, double diffusion, double spec, double shine, int rec, double alpha);

    bool intersect(Ray3D &ray, Point3D &P, Vector3D &N, Ray3D &ray_out) const override;

private:
    void draw(bool filled);
};