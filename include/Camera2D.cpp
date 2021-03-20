#include "Camera2D.hpp"
#include <math.h>
#include "GlutLibrary2D.hpp"
#include <GL/freeglut.h>
#include "Circle2D.hpp"

Camera2D::Camera2D(const Point2D &T, double theta, double focal, double distance)
{
    deform(-1., focal);
    Point2D P{T._x + distance * cos(theta), T._y + distance * sin(theta)};
    std::cout << P << std::endl;
    Vector2D u = Vector2D::vector_from_points(P, T);
    u.normalize();
    double phi = acos(u._x);
    if (u._y < 0)
    {
        phi = -phi;
    }
    rotate(phi - PI / 2);
    translate(P._x, P._y);
}

const Camera2D &Camera2D::operator=(const Camera2D &camera)
{
    _Md = camera._Md;
    return *this;
}

void Camera2D::trace_rays(std::vector<Shape2D *> objects)
{
    Point2D A = _Md * Point2D{0, -1};
    double step = 2. / _cols;
    for (int i = 0; i < _cols; i++)
    {
        Point2D B = _Md * Point2D{-1. + i * step, 0.};
        Ray2D ray{A, B, Color{1, 0, 0}}; //TODO normalize
        Vector2D N;
        Point2D P;
        double distance = INFINITY;
        for (auto &o : objects)
        {
            if (o->intersect(ray, P, N))
            {
                double distance_tmp = P.sqrtDistance(A);
                if (distance_tmp < distance)
                {
                    distance = distance_tmp;
                    B = P;
                    ray.set_color(o->get_color());
                }
            }
        }
        ray.draw();
    }
    Point2D B = _Md * Point2D{0, 0};
    Ray2D ray{A, B, Color{1, 0, 0}};
    ray.draw();
    A = _Md * Point2D{-1, 0};
    B = _Md * Point2D{1, 0};
    ray = Ray2D{A, B, Color{0, 1, 0}};
    ray.draw();
}

/*
void Camera2D::trace_rays(std::vector<Shape2D *> objects)
{

    Vector2D perpendicular_vector = Vector2D::vector_from_points(_focal.get_A(), _focal.get_B()).perpendicular().normalize();
    Point2D radius = _size / 2 * perpendicular_vector;
    Point2D start = _focal.get_A() - radius;
    Point2D end = _focal.get_A() + radius;
    Point2D init_gap = _size * perpendicular_vector / _RAYS;
    Point2D A = _focal.get_B();
    Point2D gap = init_gap;
    Point2D B = start;
    Ray2D ray{A, B, Color{1, 0, 0}};
    for (double i = 0; i <= _RAYS; i++)
    {
        gap = gap + init_gap;
        B = start + gap;
        Vector2D N;
        Point2D P;
        double distance = INFINITY;
        for (auto &o : objects)
        {
            if (o->intersect(ray, P, N))
            {
                double distance_tmp = P.sqrtDistance(A);
                if (distance_tmp < distance)
                {
                    distance = distance_tmp;
                    B = P;
                    ray.set_color(o->get_color());
                }
            }
        }
        ray.draw();
    }
    _focal.draw();
    Ray2D ray2{start, end, Color{0, 1, 0}};
    ray2.draw();
}*/