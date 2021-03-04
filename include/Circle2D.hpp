#pragma once

#include "Point2D.hpp"
#include "Shape2D.hpp"
#include "Ray2D.hpp"
#include "Matrix2D.hpp"

#define PI 3.14159265358979311599796346854

class Circle2D : public Shape2D
{
public:

    Circle2D(Color);

    void draw() const override;

    bool intersect(Ray2D& ray, Point2D &P, Vector2D &N) const override;

private :
    void draw(bool filled);

};