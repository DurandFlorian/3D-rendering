#pragma once

#include "Point2D.hpp"

class Vector2D : public Point2D
{

public:
    Vector2D(double x, double y);

    Vector2D();

    static Vector2D vector_from_points(const Point2D &A, const Point2D &B);

    const Vector2D& normalize();

    ~Vector2D();

    double cross_product(const Vector2D &v) const;

    double dot_product(const Vector2D &v) const;

    Vector2D perpendicular() const;
};