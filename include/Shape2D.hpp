#pragma once
#include "Vector2D.hpp"
#include <math.h>

#define SQRT2 sqrt(2)
#define CANONICAL_CENTER Point2D{0,0}

class Ray2D;

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