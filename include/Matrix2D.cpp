#include "Matrix2D.hpp"
#include <math.h>

Matrix2D::Matrix2D()
{
}

Matrix2D::Matrix2D(const Matrix2D &m) : _matrix{m._matrix}
{
}

Matrix2D Matrix2D::operator*(const Matrix2D &m)
{
    Matrix2D new_matrix{};
    for (uint8_t i = 0; i < _rows; i++)
    {
        for (uint8_t j = 0; j < _cols; j++)
        {
            new_matrix._matrix[3 * i + j] = 0;
            for (uint8_t k = 0; k < _rows; k++)
            {
                new_matrix._matrix[3 * i + j] += _matrix[3 * i + k] * m._matrix[3 * k + j];
            }
        }
    }
    return new_matrix;
}

Point2D Matrix2D::operator*(Point2D &P)
{
    Point2D N;
    N._x = _matrix[0] * P._x + _matrix[1] * P._y + _matrix[2] * 1;
    N._y = _matrix[3] * P._x + _matrix[4] * P._y + _matrix[5] * 1;
    return N;
}

const Matrix2D &Matrix2D::operator=(const Matrix2D &m)
{
    this->_matrix = m._matrix;
    return *this;
}

Matrix2D Matrix2D::rotation(double theta)
{
    Matrix2D m;
    m._matrix = {
        cos(theta),
        -sin(theta),
        0,
        sin(theta),
        cos(theta),
        0,
        0,
        0,
        1};
    return m;
}

Matrix2D Matrix2D::translation(double x, double y)
{
    Matrix2D m;
    m._matrix = {
        1,
        0,
        x,
        0,
        1,
        y,
        0,
        0,
        1};
    return m;
}

Matrix2D Matrix2D::homothety(double a, double b)
{
    Matrix2D m;
    m._matrix = {
        a,
        0,
        0,
        0,
        b,
        0,
        0,
        0,
        1};
    return m;
}
