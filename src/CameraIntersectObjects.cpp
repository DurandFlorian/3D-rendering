#include <iostream>
#include <GL/freeglut.h>
#include "../include/Ray2D.hpp"
#include "../include/Circle2D.hpp"
#include "../include/GlutLibrary2D.hpp"
#include "../include/Camera2D.hpp"
#include "../include/Square2D.hpp"
#include "../include/ScrolBars.hpp"
#include <vector>

using namespace std;

/* tailles de la fenêtre (en pixel) */
static int WWIDTH = 512, WHEIGHT = 512;

//taile de l'écran
static int SWIDTH = 1920, SHEIGHT = 1080;

/* limites de la zone reelle associee a la fenetre */
static double wxmin = -10., wymin = -12., wxmax = +10., wymax = +10;

Point2D C, D;
ScrolBar *rotation_bar, *focal_bar;
Camera2D *camera;
double s = 2;
vector<Shape2D *> objects;

void draw()
{
    camera->trace_rays(objects);
    for (auto o : objects)
    {
        (*o).draw();
    }
}

void init()
{
    C = Point2D{2, 2};
    D = Point2D{-4, -4};

    camera = new Camera2D{Point2D{0, 0}, -1.2 * PI, 1, 4};
    Circle2D *c1 = new Circle2D{Color{0, 0, 1}};
    rotation_bar = new ScrolBar(0, 2 * PI, [](double r) { camera->rotate_on_center(r); });
    addScrollBar(*rotation_bar);
    focal_bar = new ScrolBar(1, 2, [](double l) { camera->focal_length(l); });
    addScrollBar(*focal_bar);
    c1->translate(2, 0);
    c1->deform(2, 1);
    c1->rotate(PI / 2);
    Point2D *p1 = new Point2D{wxmin, wymin + 2};
    Point2D *p2 = new Point2D{wxmin, wymax};
    Point2D *p3 = new Point2D{wxmax, wymax};
    Point2D *p4 = new Point2D{wxmax, wymin + 2};
    Ray2D *r1 = new Ray2D{*p1, *p2, Color{0, 0.2, 0}};
    Ray2D *r2 = new Ray2D{*p2, *p3, Color{0, 0.2, 0}};
    Ray2D *r3 = new Ray2D{*p3, *p4, Color{0, 0.2, 0}};
    Ray2D *r4 = new Ray2D{*p4, *p1, Color{0, 0.2, 0}};

    Square2D *s1 = new Square2D{Color{1, 1, 0}};
    s1->translate(-3, 0).deform(1, 2).rotate(PI / 2);
    objects.emplace_back(s1);
    objects.emplace_back(c1);
    objects.emplace_back(r1);
    objects.emplace_back(r2);
    objects.emplace_back(r3);
    objects.emplace_back(r4);
}

void update()
{
}

void quit()
{
}

int main(int argc, char **argv)
{
    glut2DInit(argc, argv, WWIDTH, WHEIGHT, SWIDTH, SHEIGHT, wxmin, wymin, wxmax, wymax, init, update);
    glut2Ddraw(draw);
    glut2Dexit(quit);
    return 0;
}