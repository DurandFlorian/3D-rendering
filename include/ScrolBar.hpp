#pragma once

#include "Point.hpp"
#include <functional>

class ScrolBar
{
public:
    ScrolBar(double min, double max, std::function<void(double)> function) : _min{min}, _max{max}, _value{min}, function{function}
    {
    }

    double get_min()
    {
        return _min;
    }

    double get_max()
    {
        return _max;
    }

    double get_value()
    {
        return _value;
    }

    Point2D &get_cursor()
    {
        return _cursor;
    }

    void move(double x, double xmin, double xmax)
    {
        _cursor.x() = x;
        _previous_value = _value;
        _value = _min + ((_max - _min) * ((x - xmin) / (xmax - xmin)));
        function(_value - _previous_value);
    }

private:
    double _min;
    double _max;
    double _value;
    double _previous_value;
    Point2D _cursor;
    std::function<void(double)> function;
};