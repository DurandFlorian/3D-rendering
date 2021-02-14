#include <iostream>
#include <GL/freeglut.h>
#include "../lib/Draw.hpp"
#include "../lib/ControllablePoints.hpp"

using namespace std;

/* tailles de la fenêtre (en pixel) */
static int WWIDTH=512, WHEIGHT=512;

//taile de l'écran
static int SWIDTH=1920, SHEIGHT= 1080;

/* limites de la zone reelle associee a la fenetre */
static double wxmin=-10.,wymin=-10.,wxmax=+10.,wymax=+10.;

ControllablePoints points{};
 
void Draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0,0);
    points.draw();
    glFlush();
}

void init(){
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(wxmin, wxmax,wymin, wymax);
    points.add(Point2D{-5,-5});
    points.add(Point2D{5,5});
}

void mouse(int button, int state, int x, int y){
    double i = x/(double)WWIDTH*(2*wxmax)-wxmax;
    double j = -(y/(double)WHEIGHT*(2*wymax)-wymax);
    if( button == GLUT_LEFT_BUTTON){
        if(state==GLUT_DOWN){
            points.click(Point2D{i,j});
        }else{
            points.release();
        }
    }
}

void motion(int x,int y){
    double i = x/(double)WWIDTH*(2*wxmax)-wxmax;
    double j = -(y/(double)WHEIGHT*(2*wymax)-wymax);
    points.move(Point2D{i,j});
    glutPostRedisplay();
}

void quit(){
    std::cout << "Exit" << std::endl;
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WWIDTH, WHEIGHT);
    glutInitWindowPosition((SWIDTH-WWIDTH)/2, (SHEIGHT-WHEIGHT)/2);
    glutCreateWindow("squelette");
    init();
    glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS ); 
    glutDisplayFunc(Draw);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    quit();
    return 0;
}