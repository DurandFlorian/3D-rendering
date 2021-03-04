#pragma once

#include "Point2D.hpp"
#include "Shape2D.hpp"

class Square2D : public Shape2D
{

public:
    Square2D(Color color);

    void draw() const override;

    bool intersect(Ray2D& ray, Point2D &P, Vector2D &N) const override;

private:
};