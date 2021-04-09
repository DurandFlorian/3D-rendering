#pragma once

#include "Point.hpp"
#include "Shape3D.hpp"
#include "Ray3D.hpp"
#include "Matrix3D.hpp"

class Square3D : public Shape3D
{
public:
    Square3D(Color, double diffusion, double spec, double shine, int rec, double alpha);

    bool intersect(Ray3D &ray, Point3D &P, Vector3D &N, Ray3D &ray_out) const override;
};