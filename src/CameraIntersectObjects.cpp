#include <iostream>
#include <GL/freeglut.h>
#include "../include/Ray2D.hpp"
#include "../include/Circle2D.hpp"
#include "../include/GlutLibrary2D.hpp"
#include "../include/Camera2D.hpp"
#include "../include/Square2D.hpp"
#include <vector>

using namespace std;

/* tailles de la fenêtre (en pixel) */
static int WWIDTH = 512, WHEIGHT = 512;

//taile de l'écran
static int SWIDTH = 1920, SHEIGHT = 1080;

/* limites de la zone reelle associee a la fenetre */
static double wxmin = -10., wymin = -10., wxmax = +10., wymax = +10.;

Point2D A, B, C, D;
Camera2D camera;
double s = 2;
vector<Shape2D *> objects;

void draw()
{
    camera.trace_rays(objects);
    for (auto o : objects)
    {
        (*o).draw();
    }
}

void init()
{
    A = Point2D{5, 5};
    B = Point2D{0, 0};
    C = Point2D{2, 2};
    D = Point2D{-4, -4};
    addControllablePoint(&A);
    addControllablePoint(&B);
    addControllablePoint(&C);
    addControllablePoint(&D);
    Ray2D ray{A, B};
    camera = Camera2D{ray, s};
    Circle2D *c1 = new Circle2D{C, 3};
    Circle2D *c2 = new Circle2D{D, 3};
    Point2D *p1 = new Point2D{wxmin, wymin};
    Point2D *p2 = new Point2D{wxmin, wymax};
    Point2D *p3 = new Point2D{wxmax, wymax} ;
    Point2D *p4 = new Point2D{wxmax, wymin};
    Ray2D *r1 = new Ray2D{*p1,*p2};
    Ray2D *r2 = new Ray2D{*p2,*p3};
    Ray2D *r3 = new Ray2D{*p3,*p4};
    Ray2D *r4 = new Ray2D{*p4,*p1};
    Square2D *square =  new Square2D{CANONICAL_CENTER,2};
    objects.emplace_back(c1);
    objects.emplace_back(c2);
    objects.emplace_back(r1);
    objects.emplace_back(r2);
    objects.emplace_back(r3);
    objects.emplace_back(r4);
    objects.emplace_back(square);
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