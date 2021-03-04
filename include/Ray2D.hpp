#pragma once

#include "Shape2D.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"

class Ray2D : public Shape2D
{
public:
    Ray2D(Point2D &, Point2D &,Color);

    Ray2D(const Ray2D&);

    bool intersect(Ray2D& ray, Point2D &P, Vector2D &N) const override;

    const Point2D &get_A() const;

    const Point2D &get_B() const;

    void draw() const override;

    const Ray2D &operator=(const Ray2D &);

    void set_color(const Color&  color);

private:
    Point2D &_A;
    Point2D &_B;
};