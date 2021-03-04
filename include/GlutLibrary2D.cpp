#include "GlutLibrary2D.hpp"
#include <GL/freeglut.h>
#include "ControllablePoints.hpp"

void (*d)(void) = nullptr;
void (*u)(void) = nullptr;

int width,height;
double xmax,ymax;

ControllablePoints points{};

void glut2DInit(int argc, char **argv, int WWIDTH, int WHEIGHT, int SWIDTH, int SHEIGHT, double wxmin, double wymin, double wxmax, double wymax, void (*init)(void),void (*update)(void))
{
    u=update;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WWIDTH, WHEIGHT);
    glutInitWindowPosition((SWIDTH - WWIDTH) / 2, (SHEIGHT - WHEIGHT) / 2);
    glutCreateWindow("Glut 2D");
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(wxmin, wxmax, wymin, wymax);
    width = WWIDTH;
    height = WHEIGHT;
    xmax = wxmax;
    ymax = wymax;
    init();
    u();
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}

void drawAll()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0, 0);
    points.draw();
    d();
    glFlush();
}

void mouse(int button, int state, int x, int y){
    double i = x/(double)width*(2*xmax)-xmax;
    double j = -(y/(double)height*(2*ymax)-ymax);
    if( button == GLUT_LEFT_BUTTON){
        if(state==GLUT_DOWN){
            points.click(Point2D{i,j});
        }else{
            points.release();
        }
    }
}

void motion(int x,int y){
    double i = x/(double)width*(2*xmax)-xmax;
    double j = -(y/(double)height*(2*ymax)-ymax);
    points.move(Point2D{i,j});
    u();
    glutPostRedisplay();
}

void glut2Ddraw(void (*draw)(void))
{
    d=draw;
    glutDisplayFunc(drawAll);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
}

void glut2Dexit(void (*quit)(void)){
    quit();
    std::cout << "Exit" << std::endl;
}

void addControllablePoint(Point2D* point){
    points.add(point);
}