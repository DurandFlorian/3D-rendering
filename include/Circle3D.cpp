#include "Circle3D.hpp"
#include "Ray3D.hpp"
#include <GL/freeglut.h>
#include <math.h>

Circle3D::Circle3D(Color color, double diffusion, double spec, double shine, int rec) : Shape3D(color, diffusion, spec, shine, rec)
{
}

bool Circle3D::intersect(Ray3D &ray, Point3D &P, Vector3D &N) const
{
    Point3D A = _Mi * ray.get_A();
    Point3D B = _Mi * ray.get_B();
    Vector3D opposite_vector = Vector3D::vector_from_points(A, CANONICAL_CENTER);
    Vector3D normalized_vector = Vector3D::vector_from_points(A, B).normalize();
    double t = normalized_vector.dot_product(opposite_vector);
    if (t < 0.)
    {
        return false;
    }
    Point3D T = A + t * normalized_vector;
    double d = CANONICAL_CENTER.sqrtDistance(T);
    if (d > 1.)
    {
        return false;
    }
    double e = t - sqrt(1. - d);
    P = A + e * normalized_vector;
    N = _Mn * Vector3D::vector_from_points(CANONICAL_CENTER, P).normalize();
    P = _Md * P;
    return true;
}