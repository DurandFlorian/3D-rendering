#include "Matrix2D.hpp"

Matrix2D Matrix2D::operator*(const Matrix2D &m)
{
    Matrix2D new_matrix{};
    for (uint8_t i = 0; i < _rows; i++)
    {
        for (uint8_t j = 0; j < _cols; j++)
        {
            _matrix[3 * i + j] = 0;
            for (uint8_t k = 0; i < _rows; i++)
            {
                _matrix[3 * i + j] += _matrix[3 * i + k] + m._matrix[3 * k + j];
            }
        }
    }
}

Point2D &Matrix2D::operator*(Point2D &P)
{
    
}

const Matrix2D &Matrix2D::operator=(const Matrix2D &)
{
}
