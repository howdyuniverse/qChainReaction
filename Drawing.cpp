#include "Drawing.h"

#include <QtOpenGL>
#include <cmath>
#include <QGLWidget>

Drawing::Drawing()
{
    initCircleCoords();
}

Drawing::~Drawing()
{
    glDeleteLists(1, 1);
}

void Drawing::initDisplayList()
{
    glNewList(1, GL_COMPILE);
        glBegin (GL_TRIANGLE_FAN);
            for(int i = 0; i < 65; ++i)   glVertex2fv( circle[i] );
        glEnd();
    glEndList();
}

void Drawing::initCircleCoords()
{
    int i = 1;
    circle[0][0] = 0;   // На первом элементе масива устанавливаем центр окружности
    circle[0][1] = 0;
    for (float a = 0; a < 2 * 3.14; a += 0.1, i++) 
    {
        circle[i][0] = cos(a);
        circle[i][1] = sin(a);
    }
    circle[64][0] = 1; // Дорисовуем окружность на 65 элементе
    circle[64][1] = 0;
}

void Drawing::drawCircle(float x, float y, float radius, unsigned char *colors)
{
    glPushMatrix();

    glTranslatef(x, y, 0);          // Перемещение матрицы
    glScalef(radius, radius, 1);    // Увеличение матрицы
    glColor4ubv(colors);

    glCallList(1);
//   glBegin (GL_TRIANGLE_FAN);
//      for(int i = 0; i < 65; ++i)   glVertex2fv( circle[i] );
//   glEnd();

    glPopMatrix();
}

void Drawing::drawInfoPanel()
{
    glColor4ub(0, 0, 0, 100);
    glRectf(0, 0, 700, 25);
}

void Drawing::drawWindowWin()
{
    glColor4ub(52, 63, 79, 80);
    glRectf(0, 0, 700, 430);

    glColor4ub(0, 0, 0, 100);
    glRectf(145, 150, 565, 250);
}

void Drawing::drawWidnowRepeat()
{
    glColor4ub(255, 0, 0, 60);
    glRectf(0, 0, 700, 430);

    glColor4ub(0, 0, 0, 100);
    glRectf(145, 150, 565, 250);
}

void Drawing::drawFinalBackground()
{
    glColor4ub(0, 240, 0, 60);
    glRectf(0, 0, 700, 430);

    glColor4ub(0, 0, 0, 100);
    glRectf(145, 150, 565, 250);
}
