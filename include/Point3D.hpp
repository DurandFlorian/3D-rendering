#pragma once

#include <iostream>

class Point3D
{
public:
    Point3D(double x, double y, double z);

    Point3D(const Point3D &p);

    Point3D();

    double distance(const Point3D &B) const;

    double sqrtDistance(const Point3D &B) const;

    friend std::ostream &operator<<(std::ostream &os, const Point3D &p);

    friend Point3D operator+(const Point3D &u, const Point3D &v);

    friend Point3D operator-(const Point3D &u, const Point3D &v);

    friend Point3D operator/(const Point3D &u, const double t);

    friend Point3D operator*(const double t, const Point3D &u);

    friend Point3D operator*(const Point3D &u, const double t);
    
    const Point3D &operator=(const Point3D &);

    virtual ~Point3D();

    double _x = 0;
    double _y = 0;
    double _z = 0;
};