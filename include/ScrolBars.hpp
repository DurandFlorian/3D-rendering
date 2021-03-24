#pragma once
#include <vector>
#include "ScrolBar.hpp"
#include <GL/freeglut.h>
#include "Color.hpp"
#include "GlutLibrary3D.hpp"

class ScrolBars
{
public:
    ScrolBars(Point2D up_left, Point2D down_right) : up_left{up_left}, down_right{down_right}, size{up_left._y - down_right._y}
    {
    }

    void add(ScrolBar &scrolbar)
    {
        list.emplace_back(&scrolbar);
        auto y = up_left._y - (size / list.size() / 2.);
        for (uint8_t i = 0; i < list.size(); i++)
        {
            list[i]->get_cursor()._x = up_left._x;
            list[i]->get_cursor()._y = y - i * (size / list.size());
        }
    }

    void release()
    {
        selected = nullptr;
    }

    void click(const Point2D &B)
    {
        if (list.empty())
        {
            selected = nullptr;
            return;
        }
        selected = list.front();
        auto last_distance = selected->get_cursor().sqrtDistance(B);
        for (auto p : list)
        {
            auto distance = p->get_cursor().sqrtDistance(B);
            std::cout << "distance :" << distance <<" " << p->get_cursor() << B <<std::endl;
            if (distance < last_distance)
            {
                selected = p;
                last_distance = distance;
            }
        }
    }

    void move(const Point2D &B)
    {
        if (selected)
        {
            if (B._x > up_left._x && B._x < down_right._x)
            {
                selected->move(B._x, up_left._x, down_right._x);
            }
        }
    }

    void draw()
    {
        Point2D up_right{down_right._x, up_left._y};
        Point2D down_left{up_left._x, down_right._y};
        Color color{1, 1, 1};
        color.set_color();
        glBegin(GL_QUADS);
        up_left.draw();
        up_right.draw();
        down_right.draw();
        down_left.draw();
        glEnd();
        color = Color{0.5, 0.5, 0.5};
        double step = size / list.size();
        Point2D A, B, C, D;
        for (uint8_t i = 0; i < list.size(); i++)
        {
            A = Point2D{up_left._x, up_left._y - i * step};
            B = Point2D{down_right._x, up_left._y - i * step};
            C = Point2D{down_right._x, up_left._y - (i + 1) * step};
            D = Point2D{up_left._x, up_left._y - (i + 1) * step};
            color.set_color();
            glBegin(GL_QUADS);
            A.draw();
            B.draw();
            C.draw();
            D.draw();
            glEnd();
            Point2D P = list[i]->get_cursor();
            drawSquare(P, step, Color{1, 0, 0});
        }
    }

private:
    std::vector<ScrolBar *> list;
    ScrolBar *selected;
    Point2D up_left;
    Point2D down_right;
    double size;
};