#pragma once

#include "Point3D.hpp"

class Vector3D : public Point3D
{

public:
    Vector3D(double x, double y, double z);

    Vector3D();

    static Vector3D vector_from_points(const Point3D &A, const Point3D &B);

    const Vector3D &normalize();

    ~Vector3D();

    Vector3D cross_product(const Vector3D &v) const;

    double dot_product(const Vector3D &v) const;

    friend Vector3D operator/(const Vector3D &u, const Vector3D &v);

    friend Vector3D operator*(double d, const Vector3D &v);

    friend Vector3D operator-(const Vector3D &u, const Vector3D &v);

    friend Vector3D operator+(const Vector3D &u, const Vector3D &v);

    Vector3D operator-() const;
};