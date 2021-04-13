#include "Square3D.hpp"
#include "Ray3D.hpp"
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>

Square3D::Square3D(Color color, double diffusion, double spec, double shine, double alpha) : Shape3D(color, diffusion, spec, shine, alpha)
{
}

bool Square3D::intersect(Ray3D &ray, Point3D &P, Vector3D &N, Ray3D &ray_out) const
{
    Point3D A = _Mi * ray.get_A();
    Vector3D u = ray.get_vector().normalize();
    bool flag[6] = {false, false, false, false, false, false};
    static Vector3D square_sides[6] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
    flag[0] = A.x() >= 1.;
    flag[1] = A.x() <= -1.;
    flag[2] = A.y() >= 1.;
    flag[3] = A.y() <= -1.;
    flag[4] = A.z() >= 1.;
    flag[5] = A.z() <= -1.;
    for (int i = 0; i < 6; i++)
    {
        if (!flag[i])
        {
            continue;
        }
        double ps1 = Vector3D::vector_from_points(A, square_sides[i]).dot_product(square_sides[i]);
        if (ps1 >= 0.)
        {
            continue;
        }
        double ps2 = u.dot_product(square_sides[i]);
        if (ps2 >= 0.)
        {
            continue;
        }
        double t = ps1 / ps2;
        P = A + t * u;
        if (std::max({fabs(P.x()), fabs(P.y()), fabs(P.z())}) > 1.01) //problème de coordonnées double
        {
            continue;
        }
        N = square_sides[i];
        if (_alpha > 0.)
        {
            Vector3D ut = Vector3D::VctTransmitted(-u, N, 1. / indice);
            for (int j = 0; j < 6; j++)
            {
                double ps1 = Vector3D::vector_from_points(P, square_sides[j]).dot_product(square_sides[j]);

                double ps2 = ut.dot_product(square_sides[j]);
                if (ps2 >= 0.)
                {
                    continue;
                }
                double t = ps1 / ps2;
                Point3D J = P + t * ut;
                if (std::max({fabs(J.x()), fabs(J.y()), fabs(J.z())}) > 1.01) //problème de coordonnées double
                {
                    continue;
                }
                Vector3D Nj = square_sides[j];
                J = _Md * J;
                ray_out = Ray3D{J, (_Mn * Vector3D::VctTransmitted(-ut, Nj, indice / 1.))};
                break;
            }
        }
        N = _Mn * N;
        P = _Md * P;
        return true;
    }
    return false;
}