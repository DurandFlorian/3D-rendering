#include "Ray3D.hpp"
#include <GL/freeglut.h>

Ray3D::Ray3D(Point3D &A, Point3D &B)
    : _A{A}, _B{B}
{
}

Ray3D::Ray3D(Point3D &A, Vector3D &v) : _A{A}, _B{_A + v}
{
}

const Point3D &Ray3D::get_A() const
{
    return _A;
}

const Point3D &Ray3D::get_B() const
{
    return _B;
}

const Ray3D &Ray3D::operator=(const Ray3D &ray)
{
    _A = ray._A;
    _B = ray._B;
    return *this;
}

Color Ray3D::trace(std::vector<Shape3D *> objects, std::vector<Light3D *> lights, int rec)
{
    if (rec == 0)
    {
        return Color{0, 0, 0};
    }
    double distance = INFINITY;
    Point3D P;
    Vector3D N;
    Vector3D Ntmp;
    Color color;
    Shape3D *current_object = nullptr;
    for (auto &o : objects)
    {
        if (o->intersect(*this, P, Ntmp))
        {
            double distance_tmp = P.sqrtDistance(_A);
            if (distance_tmp < distance)
            {
                distance = distance_tmp;
                _B = P;
                N = Ntmp;
                current_object = o;
            }
        }
    }
    if (current_object == nullptr)
    {
        return color;
    }
    for (auto light : lights)
    {
        Vector3D u = Vector3D::vector_from_points(_A, _B).normalize();
        Vector3D w = Vector3D::vector_from_points(_B, light->position()).normalize();
        N.normalize();
        Vector3D ur = (-2 * N.dot_product(u) * N + u).normalize();
        Ray3D Rr{_B, ur}; //TODO revoir ray construction avec un vecteur
        if (rec == -1)
        {
            rec = current_object->get_rec();
        }
        color = color + current_object->get_color(N, w, *light, u) + current_object->get_spec() * Rr.trace(objects, lights, rec - 1);
    }
    return color;
}
