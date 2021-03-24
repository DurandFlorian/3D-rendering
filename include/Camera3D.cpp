#include "Camera3D.hpp"
#include <math.h>
#include "GlutLibrary3D.hpp"
#include <GL/freeglut.h>
#include "Circle3D.hpp"

Camera3D::Camera3D(const Point3D &T, double alpha, double beta, double focal, double distance)
{
    deform(1., 1., focal);
    rotate_z(-PI / 2);
    Point3D P{T._x + distance * cos(alpha) * sin(beta), T._y + distance * sin(alpha) * sin(beta), T._z + distance * cos(beta)};
    Vector3D u = Vector3D::vector_from_points(P, T);
    u.normalize();
    double theta = acos(u._z);
    rotate_y(theta);
    if (fabs(theta) > 1e-8)
    {
        double phi = acos(u._x / sin(theta));
        if (u._y < 0)
        {
            phi = -phi;
        }
        rotate_z(phi);
    }
    translate(P._x, P._y, P._z);
}

const Camera3D &Camera3D::operator=(const Camera3D &camera)
{
    _Md = camera._Md;
    return *this;
}

void Camera3D::trace_rays(std::vector<Shape3D *> objects, std::vector<Light3D> lights)
{
    Point3D A = _Md * Point3D{0, 0, -1};
    double xstep = 2. / _cols;
    double ystep = 2. / _rows; //TODO voir comment dessiner aux bonne coordonnées
    std::vector<Color> screen(_rows * _cols);
    for (int x = 0; x < _rows; x++)
    {
        for (int y = 0; y < _cols; y++)
        {
            Point3D B = _Md * Point3D{-1. + x * xstep, -1 + y * ystep, 0.};
            Vector3D N;
            Point3D P;
            Ray3D ray{A, B, Color{0, 0, 0}}; //TODO normalize

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
                        for (auto light : lights)
                        {
                            ray.set_color(o->get_color(N, Vector3D::vector_from_points(P, light.position()), light, Vector3D::vector_from_points(ray.get_A(), ray.get_B())));
                        }
                    }
                }
            }
            screen[x * _cols + y] = ray.get_color();
        }
    }
    draw_screen(screen, _rows, _cols);
}