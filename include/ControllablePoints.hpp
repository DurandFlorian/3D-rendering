#pragma once

#include <vector>
#include "Point2D.hpp"

class ControllablePoints
{
public:
    virtual ~ControllablePoints();

    void add(Point2D *P);

    void click(const Point2D &B);

    void release();

    void move(const Point2D &B);

    void draw();

private:
    std::vector<Point2D *> list;
    Point2D *selected = nullptr;
};