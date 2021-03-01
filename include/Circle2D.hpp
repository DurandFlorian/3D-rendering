#pragma once

#include "Point2D.hpp"

#include "Shape2D.hpp"
#include "Ray2D.hpp"
#include "Matrix2D.hpp"

#define PI  3.14159265358979311599796346854

class Circle2D : public Shape2D
{
public :

    void draw_filled();

    void draw();

    bool intersect(const Ray2D ray, Point2D &P, Vector2D &N) override;
};