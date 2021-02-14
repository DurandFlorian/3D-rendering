#pragma once

#include "Point2D.hpp"

void glut2DInit(int argc, char **argv, int WWIDTH, int WHEIGHT, int SWIDTH, int SHEIGHT, double wxmin, double wymin, double wxmax, double wymax, void (*init)(void),void (*update)(void));

void glut2Ddraw(void (*draw)(void));

void glut2Dexit(void (*exit)(void));

void addControllablePoint(Point2D* point);
