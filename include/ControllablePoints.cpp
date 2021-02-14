#include "ControllablePoints.hpp"

ControllablePoints::~ControllablePoints()
{
}

void ControllablePoints::add(Point2D *P)
{
    list.emplace_back(P);
}

void ControllablePoints::click(const Point2D &B)
{

    if (list.empty())
    {
        selected = nullptr;
        return;
    }
    selected = list.front();
    auto last_distance = (*selected).distance(B);
    for (auto p : list)
    {
        auto distance = p->distance(B);
        if (distance < last_distance)
        {
            selected = p;
            last_distance = distance;
        }
    }
}

void ControllablePoints::release()
{
    selected = nullptr;
}

void ControllablePoints::move(const Point2D &B)
{
    if (selected)
    {
        *selected = B;
    }
    return;
}

void ControllablePoints::draw()
{
    for (auto p : list)
    {
        p->draw();
    }
}
