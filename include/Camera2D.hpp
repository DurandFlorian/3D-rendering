#pragma once

#include "Ray2D.hpp"
#include "Shape2D.hpp"
#include <vector>

class Camera2D
{
public:
    Camera2D(const Point2D &T, double theta, double focal, double distance);

    void trace_rays(std::vector<Shape2D *> objects);

    const Camera2D &operator=(const Camera2D &);

    Camera2D &rotate(double theta)
    {
        _Md = Matrix2D::rotation(theta) * _Md;
        return *this;
    }

    Camera2D &rotate_on_center(double theta)
    {
        Point2D C = _Md * Point2D{0, 0};
        translate(-C._x, -C._y);
        rotate(theta);
        translate(C._x, C._y);
        return *this;
    }

    Camera2D &focal_length(double length)
    {
        Point2D C = _Md * Point2D{0, 0};
        translate(-C._x, -C._y);
        Vector2D CA = Vector2D::vector_from_points(Point2D{0, 0}, _Md * Point2D{0, -1});
        Vector2D CB = Vector2D::vector_from_points(Point2D{0, 0}, Point2D{0, -1});
        double theta = atan2(CA.cross_product(CB), CA.dot_product(CB));
        rotate(theta);
        deform(1, 1 + length);
        rotate(-theta);
        translate(C._x, C._y);
        return *this;
    }

    Camera2D &translate(double x, double y)
    {
        _Md = Matrix2D::translation(x, y) * _Md;
        return *this;
    }

    Camera2D &deform(double a, double b)
    {
        _Md = Matrix2D::homothety(a, b) * _Md;
        return *this;
    }

private:
    Matrix2D _Md;
    static constexpr int _cols = 1000;
};
