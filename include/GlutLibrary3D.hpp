#pragma once

#include "Point.hpp"
#include "Color.hpp"
#include "vector"

class ScrolBar;

void glut3DInit(int argc, char **argv, int WWIDTH, int WHEIGHT, int SWIDTH, int SHEIGHT, void (*init)(void), void (*update)(void));

void drawAll();

void draw_screen(std::vector<Color> screen, int rows, int cols);

void mouse(int button, int state, int x, int y);

void motion(int x, int y);

void glut3Ddraw(void (*draw)(void));

void glut3Dexit(void (*quit)(void));

void addScrollBar(ScrolBar &scrolBar);

void drawSquare(Point2D &position, double size, Color color);