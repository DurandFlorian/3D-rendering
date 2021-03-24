#include "Color.hpp"
#include <GL/freeglut.h>

Color::Color(double R, double G, double B) : _R{R}, _G{G}, _B{B}
{
}

Color::Color()
{
}

Color::Color(const Color &color) : Color(color._R, color._G, color._B)
{
}

void Color::set_color() const
{
    glColor3f(_R, _G, _B);
}

const Color &Color::operator=(const Color &color)
{
    _R = color._R;
    _G = color._G;
    _B = color._B;
    return *this;
}

Color operator*(double v, const Color &color)
{
    Color new_color{};
    new_color._R = color._R * v;
    new_color._G = color._G * v;
    new_color._B = color._B * v;
    return new_color;
}

Color operator+(const Color &c1, const Color &c2)
{
    Color new_color{};
    new_color._R = c1._R + c2._R;
    new_color._G = c1._G + c2._G;
    new_color._B = c1._B + c2._B;
    return new_color;
}