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