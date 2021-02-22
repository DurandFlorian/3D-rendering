#pragma once

#include <iostream>

class Point2D
{
public:
    Point2D(double x, double y);

    Point2D(const Point2D &p);

    Point2D();

    void draw();

    double distance(const Point2D &B) const;

    double sqrtDistance(const Point2D &B) const;

    friend std::ostream &operator<<(std::ostream &os, const Point2D &p);

    friend Point2D operator+(const Point2D &u, const Point2D &v);

    friend Point2D operator-(const Point2D &u, const Point2D &v);

    friend Point2D operator/(const Point2D &u, const double t);

    friend Point2D operator*(const double t, const Point2D &u);

    friend Point2D operator*(const Point2D &u, const double t);

    const Point2D& operator=(const Point2D&);

    virtual ~Point2D();

    double _x = 0;
    double _y = 0;
};