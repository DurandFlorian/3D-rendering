#include <iostream>
#include <GL/freeglut.h>
#include "Draw.hpp"
#include "ControllablePoints.hpp"

using namespace std;

/* tailles de la fenêtre (en pixel) */
static int WWIDTH=512, WHEIGHT=512;

//taile de l'écran
static int SWIDTH=1920, SHEIGHT= 1080;

/* limites de la zone reelle associee a la fenetre */
static double wxmin=-10.,wymin=-10.,wxmax=+10.,wymax=+10.;

ControllablePoints points{};

time_t timer = 0;
 
void Draw(){
    std::cout << "draw" << std::endl;
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

void animate()
{
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = timeSinceStart - timer;
    if(deltaTime > 500){
        //DO
        timer = timeSinceStart;
        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y){
    std::cout << "mouse" << std::endl;
    if( button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            points.click(Point2D{(double)x/(double)WWIDTH,(double)y/(double)WHEIGHT});
        }else{
            points.release();
        }
    }
}

void motion(int x,int y){
    std::cout << "motion" << std::endl;
    points.move(Point2D{(double)x/(double)WWIDTH,(double)y/(double)WHEIGHT});
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
    //glutMotionFunc(motion);
    glutIdleFunc(animate);
    glutMainLoop();
    quit();
    return 0;
}