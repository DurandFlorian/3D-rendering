#include "Camera3D.hpp"
#include <math.h>
#include "GlutLibrary3D.hpp"
#include <GL/freeglut.h>
#include "Circle3D.hpp"

Camera3D::Camera3D(const Point3D &T, double alpha, double beta, double focal, double distance)
{
    deform(1., 1., focal);
    rotate_z(-PI / 2);
    Point3D P{T.x() + distance * cos(alpha) * sin(beta), T.y() + distance * sin(alpha) * sin(beta), T.z() + distance * cos(beta)};
    Vector3D u = Vector3D::vector_from_points(P, T);
    u.normalize();
    double theta = acos(u.z());
    rotate_y(theta);
    if (fabs(theta) > 1e-8)
    {
        double phi = acos(u.x() / sin(theta));
        if (u.y() < 0)
        {
            phi = -phi;
        }
        rotate_z(phi);
    }
    translate(P.x(), P.y(), P.z());
}

const Camera3D &Camera3D::operator=(const Camera3D &camera)
{
    _Md = camera._Md;
    return *this;
}

void Camera3D::trace_rays(std::vector<Shape3D *> objects, std::vector<Light3D *> lights)
{
    Point3D A = _Md * Point3D{0., 0., -1.};
    double xstep = 2. / _cols;
    double ystep = 2. / _rows;
    std::vector<Color> screen(_rows * _cols);

    for (int x = 0; x < _rows; x++)
    {
        for (int y = 0; y < _cols; y++)
        {
            Point3D B = _Md * Point3D{-1. + x * xstep, -1. + y * ystep, 0.};
            Ray3D ray{A, B};
            screen[x * _cols + y] = ray.trace(objects, lights, -1);
        }
    }
    draw_screen(screen, _rows, _cols);
}