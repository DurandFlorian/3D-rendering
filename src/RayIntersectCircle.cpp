#include <iostream>
#include <GL/freeglut.h>
#include "../include/Ray2D.hpp"
#include "../include/GlutLibrary2D.hpp"


using namespace std;

/* tailles de la fenêtre (en pixel) */
static int WWIDTH=512, WHEIGHT=512;

//taile de l'écran
static int SWIDTH=1920, SHEIGHT= 1080;

/* limites de la zone reelle associee a la fenetre */
static double wxmin=-10.,wymin=-10.,wxmax=+10.,wymax=+10.;

Point2D A,B,C,D;
Ray2D AB;
double r;
Circle2D circle;
bool flag = false;

void draw(){
    AB.draw();
    circle.draw();
    if(flag){
        D.draw();
    }
}

void init(){
    A = Point2D{-5,-5};
    B = Point2D{5,5};
    C = Point2D{0,0};
    addControllablePoint(&A);
    addControllablePoint(&B);
    addControllablePoint(&C);
    r=4; 
    AB = Ray2D{A,B};
    circle = Circle2D{C,r};
}

void update(){
    flag = AB.intersect(circle,D);
}

void quit(){
}

int main(int argc, char** argv){
    glut2DInit(argc,argv,WWIDTH,WHEIGHT,SWIDTH,SHEIGHT,wxmin,wymin,wxmax,wymax,init,update);
    glut2Ddraw(draw);
    glut2Dexit(quit);
    return 0;
}