#pragma once

#include <array>
#include "Point2D.hpp"

class Matrix2D
{
public:
    Matrix2D();

    Matrix2D(const Matrix2D&);

    Matrix2D operator*(const Matrix2D &);

    Point2D operator*(Point2D &P);

    const Matrix2D &operator=(const Matrix2D &);

    static Matrix2D rotation(double theta);

    static Matrix2D translation(double x, double y);

    static Matrix2D homothety(double a, double b);

private:
    static const int _rows = 3;
    static const int _cols = 3;
    std::array<double, 9> _matrix{
        1,
        0,
        0,
        0,
        1,
        0,
        0,
        0,
        1};
};