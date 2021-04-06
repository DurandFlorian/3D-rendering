#pragma once

#include <array>
#include <GL/freeglut.h>
#include <algorithm>
#include <numeric>
#include <math.h>

template<typename T,u_char dimension>
class Point
{
private :
    std::array<T,dimension> values;
public:

    T& x()
    {
        static_assert(dimension >= 1);
        return values[0];
    }
    T x() const
    {
        static_assert(dimension >= 1);
        return values[0];
    }

    T& y()
    {
        static_assert(dimension >= 2);
        return values[1];
    }
    T y() const
    {
        static_assert(dimension >= 2);
        return values[1];
    }

    T& z()
    {
        static_assert(dimension >= 3);
        return values[2];
    }
    T z() const
    {
        static_assert(dimension >= 3);
        return values[2];
    }
    
    Point() = default;

    template<typename... Args>
    Point(T v,Args&&... init) : values{v,static_cast<T>(std::forward<Args>(init))...}
    {}

    void draw() const
    {
        if constexpr ( dimension==2){
            if constexpr(std::is_same_v<T,double>){
                glVertex2dv(values.data());
            }else if constexpr(std::is_same_v<T,float>){
                glVertex2f(values.data());
            }
        }else if constexpr ( dimension==3){
            if constexpr(std::is_same_v<T,double>){
                glVertex3d(values.data());
            }else if constexpr(std::is_same_v<T,float>){
                glVertex3f(values.data());
            }
        }
    }

    double distance(const Point &B) const
    {
        return std::sqrt(sqrtDistance(B));
    }

    double sqrtDistance(const Point &B) const
    {
        return std::transform_reduce(values.begin(), values.end(), B.values.begin(),0.,
                       [](const T& a, const T& b) { return  a+b; },[](const T& a, const T& b) { return pow((b - a),2); });
    }

    friend Point operator+(const Point &A, const Point &B)
    {
        Point P{};
        std::transform(A.values.begin(),A.values.end(),B.values.begin(),P.values.begin(),[](const T& a, const T& b) { return a + b; });
        return P ;
    }

    friend Point operator-(const Point &A, const Point &B)
    {
        Point P{};
        std::transform(A.values.begin(),A.values.end(),B.values.begin(),P.values.begin(),[](const T& a, const T& b) { return a - b; });
        return P ;
    }

    friend Point operator/(const Point &A, const double t)
    {
        Point P{};
        std::transform(A.values.begin(),A.values.end(),P.values.begin(),[t](const T& a) { return a / t; });
        return P ;
    }

    friend Point operator*(const Point &A, const double t)
    {
        Point P{};
        std::transform(A.values.begin(),A.values.end(),P.values.begin(),[t](const T& a) { return a * t; });
        return P ;
    }

    friend Point operator*(const double t,const Point &A) 
    {
        Point P{};
        std::transform(A.values.begin(),A.values.end(),P.values.begin(),[t](const T& a) { return a * t; });
        return P ;
    }

    virtual ~Point() {};
};

using Point3D = Point<double,3>;
using Point2D = Point<double,2>;