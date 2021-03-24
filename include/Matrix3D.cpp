#include "Matrix3D.hpp"

#include <math.h>

Matrix3D::Matrix3D()
{
}

Matrix3D::Matrix3D(const Matrix3D &m) : _matrix{m._matrix}
{
}

Matrix3D Matrix3D::operator*(const Matrix3D &m)
{
    Matrix3D new_matrix{};
    for (uint8_t i = 0; i < _rows; i++)
    {
        for (uint8_t j = 0; j < _cols; j++)
        {
            new_matrix._matrix[_rows * i + j] = 0;
            for (uint8_t k = 0; k < _rows; k++)
            {
                new_matrix._matrix[_rows * i + j] += _matrix[_rows * i + k] * m._matrix[_rows * k + j];
            }
        }
    }
    return new_matrix;
}

const Point3D Matrix3D::operator*(const Point3D &P) const
{
    Point3D N;
    N._x = _matrix[0] * P._x + _matrix[1] * P._y + _matrix[2] * P._z + _matrix[3] * 1;
    N._y = _matrix[4] * P._x + _matrix[5] * P._y + _matrix[6] * P._z + _matrix[7] * 1;
    N._z = _matrix[8] * P._x + _matrix[9] * P._y + _matrix[10] * P._z + _matrix[11] * 1;
    return N;
}

const Vector3D Matrix3D::operator*(const Vector3D &P) const
{
    Vector3D N;
    N._x = _matrix[0] * P._x + _matrix[1] * P._y + _matrix[2] * P._z + _matrix[3] * 1;
    N._y = _matrix[4] * P._x + _matrix[5] * P._y + _matrix[6] * P._z + _matrix[7] * 1;
    N._z = _matrix[8] * P._x + _matrix[9] * P._y + _matrix[10] * P._z + _matrix[11] * 1;
    return N;
}

const Matrix3D &Matrix3D::operator=(const Matrix3D &m)
{
    this->_matrix = m._matrix;
    return *this;
}

Matrix3D Matrix3D::rotation_x(double alpha)
{
    Matrix3D m;
    m._matrix = {
        1,
        0,
        0,
        0,
        0,
        cos(alpha),
        -sin(alpha),
        0,
        0,
        sin(alpha),
        cos(alpha),
        0,
        0,
        0,
        0,
        1};
    return m;
}

Matrix3D Matrix3D::rotation_y(double beta)
{
    Matrix3D m;
    m._matrix = {
        cos(beta),
        0,
        sin(beta),
        0,
        0,
        1,
        0,
        0,
        -sin(beta),
        0,
        cos(beta),
        0,
        0,
        0,
        0,
        1};
    return m;
}

Matrix3D Matrix3D::rotation_z(double gamma)
{
    Matrix3D m;
    m._matrix = {
        cos(gamma),
        -sin(gamma),
        0,
        0,
        sin(gamma),
        cos(gamma),
        0,
        0,
        0,
        0,
        1,
        0,
        0,
        0,
        0,
        1};
    return m;
}

Matrix3D Matrix3D::translation(double x, double y, double z)
{
    Matrix3D m;
    m._matrix = {
        1,
        0,
        0,
        x,
        0,
        1,
        0,
        y,
        0,
        0,
        1,
        z,
        0,
        0,
        0,
        1};
    return m;
}

Matrix3D Matrix3D::homothety(double a, double b, double c)
{
    Matrix3D m;
    m._matrix = {
        a,
        0,
        0,
        0,
        0,
        b,
        0,
        0,
        0,
        0,
        c,
        0,
        0,
        0,
        0,
        1};
    return m;
}
