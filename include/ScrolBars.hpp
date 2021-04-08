#pragma once
#include <vector>
#include "ScrolBar.hpp"
#include <GL/freeglut.h>
#include "Color.hpp"
#include "GlutLibrary3D.hpp"

class ScrolBars
{
public:
    ScrolBars(Point2D up_left, Point2D down_right) : up_left{up_left}, down_right{down_right}
    {
    }

    void add(ScrolBar scrolbar)
    {
        list.emplace_back(scrolbar);
        ystep = (up_left.y() - down_right.y())/list.size();
        xstep = ystep;
        auto y = up_left.y() - (ystep / 2.);
        for (uint8_t i = 0; i < list.size(); i++)
        {
            list[i].get_cursor().x() = up_left.x()-(xstep/2);
            list[i].get_cursor().y() = y - i * (ystep);
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
        selected = &(list.front());
        auto last_distance = selected->get_cursor().sqrtDistance(B);
        for (auto& p : list)
        {
            auto distance = p.get_cursor().sqrtDistance(B);
            if (distance < last_distance)
            {
                selected = &p;
                last_distance = distance;
            }
        }
    }

    void move(const Point2D &B)
    {
        if (selected)
        {
            if(B.x() < up_left.x()-(xstep/2)){
                selected->move(up_left.x()-(xstep/2), up_left.x()-(xstep/2) , down_right.x() + (xstep/2) );
            }else if(B.x() > down_right.x() + (xstep/2)){
                selected->move(down_right.x() + (xstep/2), up_left.x()-(xstep/2) , down_right.x() + (xstep/2) );
            }else
            {
                selected->move(B.x(), up_left.x()-(xstep/2) , down_right.x() + (xstep/2) );
            }
        }
    }

    void draw()
    {
        Point2D up_right{down_right.x(), up_left.y()};
        Point2D down_left{up_left.x(), down_right.y()};
        Color color{0.5, 0.5, 0.5};
        color.set_color();
        glBegin(GL_QUADS);
        up_left.draw();
        up_right.draw();
        down_right.draw();
        down_left.draw();
        glEnd();
        for (uint8_t i = 0; i < list.size(); i++)
        {
            Point2D P = list[i].get_cursor();
            drawRectangle(P, xstep,ystep, list[i].get_color());
            drawRectangle(P, xstep/2,ystep/2, Color{0,0,0});
        }
    }

private:
    std::vector<ScrolBar> list;
    ScrolBar *selected;
    Point2D up_left;
    Point2D down_right;
    double xstep;
    double ystep;
};