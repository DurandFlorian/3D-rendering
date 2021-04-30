#include "Ray3D.hpp"
#include <GL/freeglut.h>

Ray3D::Ray3D() {}

Ray3D::Ray3D(Point3D &A, Point3D &B)
    : _A{A}, _v{Vector3D::vector_from_points(A, B)}
{
}

Ray3D::Ray3D(Point3D &A, Vector3D v) : _A{A}, _v{v}
{
}

const Point3D &Ray3D::get_A() const
{
    return _A;
}

Vector3D Ray3D::get_vector() const
{
    return _v;
}

const Ray3D &Ray3D::operator=(const Ray3D &ray)
{
    _A = ray._A;
    _v = ray._v;
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
    Point3D B;
    Vector3D N;
    Vector3D Ntmp;
    Ray3D ray_out;
    Ray3D ray_out_tmp;
    Color color;
    Shape3D *current_object = nullptr;
    for (auto &o : objects)
    {
        if (o->intersect(*this, P, Ntmp, ray_out_tmp))
        {
            double distance_tmp = P.sqrtDistance(_A);
            if (distance_tmp < distance)
            {
                distance = distance_tmp;
                B = P;
                N = Ntmp;
                current_object = o;
                ray_out = ray_out_tmp;
            }
        }
    }
    if (current_object == nullptr)
    {
        return color;
    }
    Vector3D u = _v.normalize();
    N = N.normalize();
    for (auto light : lights)
    {
        Vector3D w = Vector3D::vector_from_points(B, light->position()).normalize();
        color += current_object->get_color(N, w, *light, u);
        if (current_object->get_spec() > 0.)
        {
            Vector3D ur = (-2 * N.dot_product(u) * N + u);
            Ray3D Rr{B, ur};
            color += current_object->get_spec() * Rr.trace(objects, lights, rec - 1);
        }
        if (current_object->get_alpha() > 0.)
        {
            color += current_object->get_alpha() * ray_out.trace(objects, lights, rec);
        }
    }
    return color;
}
