#include <iostream>
#include <GL/freeglut.h>
#include "../include/Ray3D.hpp"
#include "../include/Circle3D.hpp"
#include "../include/GlutLibrary2D.hpp"
#include "../include/Camera3D.hpp"
#include "../include/ScrolBars.hpp"
#include <vector>

using namespace std;

/* tailles de la fenêtre (en pixel) */
static int WWIDTH = 512, WHEIGHT = 512;

//taile de l'écran
static int SWIDTH = 1920, SHEIGHT = 1080;

/* limites de la zone reelle associee a la fenetre */
static double wxmin = -10., wymin = -12., wxmax = +10., wymax = +10;

Camera3D *camera;
double s = 2;
vector<Shape3D *> objects;

void draw()
{
    camera->trace_rays(objects);
}

void init()
{
    camera = new Camera3D{Point3D{0, 0, 0}, PI, PI, 1, 4};
    ScrolBar *rotax = new ScrolBar{0, 2 * PI, [](double theta) { camera->rotate_x(theta); }};
    ScrolBar *rotay = new ScrolBar{0, 2 * PI, [](double theta) { camera->rotate_y(theta); }};
    ScrolBar *rotaz = new ScrolBar{0, 2 * PI, [](double theta) { camera->rotate_z(theta); }};
    addScrollBar(*rotax);
    addScrollBar(*rotay);
    addScrollBar(*rotaz);
    Circle3D *c1 = new Circle3D{Color{0, 0, 1}};
    c1->deform(2, 1, 2);
    Circle3D *c2 = new Circle3D{Color{0, 1, 0}};
    c2->translate(2,0,0);
    objects.emplace_back(c1);
    objects.emplace_back(c2);
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