#include "GlutLibrary2D.hpp"
#include <GL/freeglut.h>
#include "ControllablePoints.hpp"
#include "ScrolBars.hpp"

void (*d)(void) = nullptr;
void (*u)(void) = nullptr;

int width, height;
double xmax, ymax, xmin, ymin;
#define SCROLL_SIZE 2.

ScrolBars *scrolBars;

void glut2DInit(int argc, char **argv, int WWIDTH, int WHEIGHT, int SWIDTH, int SHEIGHT, double wxmin, double wymin, double wxmax, double wymax, void (*init)(void), void (*update)(void))
{
    u = update;
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
    xmin = wxmin;
    ymin = wymin;
    scrolBars = new ScrolBars{Point2D{wxmin, wymin + SCROLL_SIZE}, Point2D{wxmax, wymin}};
    init();
    u();
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}

void drawAll()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0, 0);
    scrolBars->draw();
    d();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    double i = xmin + x / (double)width * (xmax - xmin);
    double j = ymax - y / (double)height * (ymax - ymin);
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            scrolBars->click(Point2D{i, j});
        }
        else
        {
            scrolBars->release();
        }
    }
}

void motion(int x, int y)
{
    double i = xmin + x / (double)width * (xmax - xmin);
    double j = ymax - y / (double)height * (ymax - ymin);
    scrolBars->move(Point2D{i, j});
    u();
    glutPostRedisplay();
}

void glut2Ddraw(void (*draw)(void))
{
    d = draw;
    glutDisplayFunc(drawAll);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
}

void glut2Dexit(void (*quit)(void))
{
    quit();
    std::cout << "Exit" << std::endl;
}

void addScrollBar(ScrolBar &scrolBar)
{
    scrolBars->add(scrolBar);
}

void drawSquare(Point2D &position, double size, Color color)
{
    color.set_color();
    Point2D A{position._x - size / 2, position._y + size / 2};
    Point2D B{position._x + size / 2, position._y + size / 2};
    Point2D C{position._x + size / 2, position._y - size / 2};
    Point2D D{position._x - size / 2, position._y - size / 2};
    glBegin(GL_QUADS);
    A.draw();
    B.draw();
    C.draw();
    D.draw();
    glEnd();
}

void draw_screen(std::vector<Color> screen, int rows, int cols)
{
    glBegin(GL_POINTS);
    double xstep = (xmax - xmin) / width;
    double ystep = (ymax - (ymin + SCROLL_SIZE)) / height;
    double istep = ((double)rows) / width;
    double jstep = ((double)cols) / height;
    double i = 0;
    double j = 0;
    for (double x = xmin; x < xmax; x += xstep)
    {
        j = 0;
        for (double y = (ymin + SCROLL_SIZE); y < ymax; y += ystep)
        {
            screen[(int)(i)*cols + j].set_color();
            glVertex2d(x, y);
            j += jstep;
        }
        i += istep;
    }
    glEnd();
}