#include <iostream>
#include <GL/freeglut.h>
#include "../include/Point.hpp"
#include "../include/Ray3D.hpp"
#include "../include/Circle3D.hpp"
#include "../include/Square3D.hpp"
#include "../include/Camera3D.hpp"
#include "../include/ScrolBars.hpp"
#include "../include/GlutLibrary3D.hpp"
#include <vector>

using namespace std;

/* tailles de la fenêtre (en pixel) */
static int WWIDTH = 512, WHEIGHT = 512;

//taile de l'écran
static int SWIDTH = 1920, SHEIGHT = 1080;

Camera3D *camera;
Light3D *light;
double s = 2;
vector<Shape3D *> objects;
vector<Light3D *> lights;

void draw()
{
    camera->trace_rays(objects, lights);
}

void init()
{
    camera = new Camera3D{Point3D{0, 0, 0}, 0, 0, 1, 5};
    light = new Light3D{Point3D{10, 10, 10}, Color{1, 1, 1}, 0.1};
    addScrollBar({0, 2 * PI, Color{1, 0, 0}, [](double theta) { camera->rotate_x(theta); }});
    addScrollBar({0, 2 * PI, Color{1, 0, 0}, [](double theta) { camera->rotate_y(theta); }});
    addScrollBar({0, 2 * PI, Color{1, 0, 0}, [](double theta) { camera->rotate_z(theta); }});
    addScrollBar({1, 5, Color{1, 0, 0}, [](double distance) { camera->zoom(distance); }});
    addScrollBar({10, 1000, Color{1, 0, 0}, [](double size) { camera->rows_and_columns(size); }});
    addScrollBar({0, 2 * PI, Color{0, 1, 0}, [](double theta) { light->rotate_x(theta); }});
    addScrollBar({0, 2 * PI, Color{0, 1, 0}, [](double theta) { light->rotate_y(theta); }});
    addScrollBar({0, 2 * PI, Color{0, 1, 0}, [](double theta) { light->rotate_z(theta); }});
    addScrollBar({1, 5, Color{0, 0, 1}, [](double rec) { camera->recursion(rec); }});

    Circle3D *c1 = new Circle3D{Color{0, 0, 1}, 1, 1, 0, 0};
    c1->translate(3, 0, 0);
    Circle3D *c2 = new Circle3D{Color{0, 1, 1}, 1, 0, 0, 0};
    c2->translate(-3, 0, 0);
    Circle3D *c3 = new Circle3D{Color{1, 0, 1}, 1, 0.99, 0.70, 0};
    c3->translate(0, 3, 0);
    Circle3D *c4 = new Circle3D{Color{1, 1, 0}, 1, 0, 0, 0};
    c4->translate(0, -3, 0);
    Circle3D *c5 = new Circle3D{Color{1, 0, 0}, 1, 0, 0, 0};
    c5->translate(0, 0, 3);

    Circle3D *c6 = new Circle3D{Color{0, 0, 0}, 1, 0, 0, 1};
    c6->translate(0, 0, -3);
    Square3D *s1 = new Square3D{Color{0, 0, 0}, 1, 0, 0, 1};

    objects.emplace_back(c1);
    objects.emplace_back(c2);
    objects.emplace_back(c3);
    objects.emplace_back(c4);
    objects.emplace_back(c5);
    objects.emplace_back(c6);
    objects.emplace_back(s1);
    lights.emplace_back(light);
}

void update()
{
}

void quit()
{
}

int main(int argc, char **argv)
{
    glut3DInit(argc, argv, WWIDTH, WHEIGHT, SWIDTH, SHEIGHT, init, update);
    glut3Ddraw(draw);
    glut3Dexit(quit);
    return 0;
}