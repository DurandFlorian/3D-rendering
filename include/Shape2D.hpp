#pragma once
#include "Ray2D.hpp"


class Shape2D
{
public:
    virtual void draw() = 0;

    Shape2D()
    {
    }

    virtual ~Shape2D()
    {
    }

    virtual bool intersect(const Ray2D ray,Point2D& P,Vector2D& N) = 0;
};