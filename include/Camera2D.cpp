#include "Camera2D.hpp"

Camera2D::Camera2D(Ray2D focal, double size)
    : _focal{focal}, _size{size}
{
}

Camera2D::Camera2D()
{
}

const Camera2D &Camera2D::operator=(const Camera2D &camera)
{
    _focal = camera._focal;
    _size = camera._size;
    return *this;
}

void Camera2D::trace_rays(std::vector<Shape2D*> objects)
{ //TODO : à améliorer

    Vector2D perpendicular_vector = Vector2D::vector_from_points(_focal.get_A(), _focal.get_B()).perpendicular();
    perpendicular_vector.normalize();

    Point2D start = _focal.get_A() - (_size / 2 * perpendicular_vector);
    Point2D end = _focal.get_A() + (_size / 2 * perpendicular_vector);
    Point2D gap = _size * perpendicular_vector / _RAYS;

    for (double i = 0; i <= _RAYS; i++)
    {
        Point2D A = _focal.get_B();
        Point2D B = start + i * gap;
        Vector2D AB = Vector2D::vector_from_points(A,B);
        B = B + 2* AB;
        Ray2D ray{A,B};
        Vector2D N;
        for(auto o : objects)
        {
            if((*o).intersect(ray,B,N))
            {
                break;
            }
        }
        ray.draw();
    }
    _focal.draw();
    Ray2D ray{start, end};
    ray.draw();
}