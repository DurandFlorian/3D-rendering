#pragma once

class Color
{
public:
    Color(double R, double G, double B);

    Color();

    Color(const Color &);

    void set_color() const;

    const Color &operator=(const Color &);

private:
    double _R = 0;
    double _G = 0;
    double _B = 0;
};