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