#pragma once

#include <array>
#include "Point2D.hpp"

class Matrix2D
{
public:
    Matrix2D operator*(const Matrix2D &);

    Point2D &operator*(Point2D &P);

    const Matrix2D &operator=(const Matrix2D &);

private:
    static const int _rows = 3;
    static const int _cols = 3;
    std::array<double, 9> _matrix;
};