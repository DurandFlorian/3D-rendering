#include "Circle3D.hpp"
#include "Ray3D.hpp"
#include <GL/freeglut.h>
#include <math.h>

Circle3D::Circle3D(Color color, double diffusion, double spec, double shine, double alpha) : Shape3D(color, diffusion, spec, shine, alpha)
{
}

bool Circle3D::intersect(Ray3D &ray, Point3D &P, Vector3D &N, Ray3D &ray_out) const
{

    Point3D A = _Mi * ray.get_A();
    Vector3D opposite_vector = Vector3D::vector_from_points(A, CANONICAL_CENTER);
    Vector3D u = ray.get_vector().normalize();
    double t = u.dot_product(opposite_vector);
    if (t < 0.)
    {
        return false;
    }
    Point3D T = A + t * u;
    double d = CANONICAL_CENTER.sqrtDistance(T);
    if (d > 1.)
    {
        return false;
    }
    double e = t - sqrt(1. - d);
    P = A + e * u;
    N = Vector3D::vector_from_points(CANONICAL_CENTER, P);
    if (_alpha > 0.)
    {
        Vector3D ut = Vector3D::VctTransmitted(-u, N, 1. / indice);
        Vector3D AC = Vector3D::vector_from_points(P, CANONICAL_CENTER);
        double t = ut.dot_product(AC);
        T = P + t * ut;
        double d = CANONICAL_CENTER.sqrtDistance(T);
        double e = t - sqrt(1. - d);
        Point3D J = P + e * ut;
        Vector3D Nj = Vector3D::vector_from_points(CANONICAL_CENTER, J);
        J = _Md * J;
        ray_out = Ray3D{J, (_Mn * Vector3D::VctTransmitted(-ut, Nj, indice / 1.))};
    }
    N = _Mn * N;
    P = _Md * P;
    return true;
}