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


bool flag = false;

void draw(){
    AB.draw();
    if(flag){
        Ray2D AC{A,C};
        Ray2D CD{C,D};
        AC.draw();
        CD.draw();
        D.draw();
    }
}

void init(){
    A = Point2D{-5,-5};
    B = Point2D{5,5};
    C = Point2D{-5,5};
    addControllablePoint(&A);
    addControllablePoint(&B);
    addControllablePoint(&C);
    AB = Ray2D{A,B};
}

void update(){
    flag = AB.projection(C,D);
}

void quit(){
}

int main(int argc, char** argv){
    glut2DInit(argc,argv,WWIDTH,WHEIGHT,SWIDTH,SHEIGHT,wxmin,wymin,wxmax,wymax,init,update);
    glut2Ddraw(draw);
    glut2Dexit(quit);
    return 0;
}