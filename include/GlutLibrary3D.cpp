#include "GlutLibrary3D.hpp"
#include "ScrolBars.hpp"
#include <GL/freeglut.h>
#include <iostream>

void (*d)(void) = nullptr;
void (*u)(void) = nullptr;

int width, height;
ScrolBars *scrolBars;
int scroll_size;

void glut3DInit(int argc, char **argv, int WWIDTH, int WHEIGHT, int SWIDTH, int SHEIGHT, void (*init)(void), void (*update)(void))
{
    u = update;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WWIDTH, WHEIGHT);
    glutInitWindowPosition((SWIDTH - WWIDTH) / 2, (SHEIGHT - WHEIGHT) / 2);
    glutCreateWindow("Ray tracing");
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    width = WWIDTH;
    height = WHEIGHT;
    gluOrtho2D(0, width, height,0 );
    scroll_size = height / 8;
    scrolBars = new ScrolBars{Point2D{0, (double)height - scroll_size}, Point2D{(double)width, (double)height}};
    init();
    u();
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}

void drawAll()
{
    glClear(GL_COLOR_BUFFER_BIT);
    scrolBars->draw();
    d();
    glFlush();
}

void draw_screen(std::vector<Color> screen, int rows, int cols)
{
    glBegin(GL_POINTS);
    double istep = ((double)rows) / width;
    double jstep = ((double)cols) / (height- scroll_size);
    double i = 0;
    double j = 0;
    for (int x = 0; x < width; x++)
    {
        j = 0;
        for (int y = 0; y < height- scroll_size; y++)
        {
            screen[(int)(i)*cols + j].set_color();
            glVertex2i(x, y);
            j += jstep;
        }
        i += istep;
    }
    glEnd();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            scrolBars->click(Point2D{(double)x, (double)y});
        }
        else
        {
            scrolBars->release();
        }
    }
}

void motion(int x, int y)
{
    scrolBars->move(Point2D{(double)x, (double)y});
    u();
    glutPostRedisplay();
}

void glut3Ddraw(void (*draw)(void))
{
    d = draw;
    glutDisplayFunc(drawAll);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
}

void glut3Dexit(void (*quit)(void))
{
    quit();
    std::cout << "Exit" << std::endl;
}

void addScrollBar(ScrolBar scrolBar)
{
    scrolBars->add(scrolBar);
}

void drawRectangle(Point2D position, double w,double h, Color color)
{
    color.set_color();
    Point2D A{position.x() - w / 2, position.y() + h / 2};
    Point2D B{position.x() + w / 2, position.y() + h / 2};
    Point2D C{position.x() + w / 2, position.y() - h / 2};
    Point2D D{position.x() - w / 2, position.y() - h / 2};
    glBegin(GL_QUADS);
    A.draw();
    B.draw();
    C.draw();
    D.draw();
    glEnd();
}