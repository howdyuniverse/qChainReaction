#include "Circle.h"
#include <cmath>
#include <cstdlib>

const int width = 700;
const int height = 430;

Circle::Circle()
{
    moveMode = 1;
    x = float (rand() % width);
    y = float (rand() % height);

    radius = 9.0;

    active  = true;
    disable = false;

    timer = 60;

    for(int i = 0; i < 3; ++i)
        color[i] = rand() % 255;
    color[3] = 255;
}

void Circle::genDirection()
{
    if(moveMode) {      
        vx = float (rand() % 1000 / 500.0 - 1.5);
        vy = float (rand() % 1000 / 500.0 - 1.5);
    }
    else {
        int c = rand()%100;

        if( c <= 50 )   { vx = 2.0; vy = 0.0; }
        else                { vx = 0.0; vy = 2.0; }
    }
}

void Circle::setCursorParameters()
{
    x = 400;
    y = 300;
    vx = 0;
    vy = 0;
    color[0] = 200;
    color[1] = 200;
    color[2] = 200;
    color[3] = 200;
    radius = 15.0;
}

void Circle::draw(Drawing &param_d)
{
    param_d.drawCircle(x, y, radius, color);
}

void Circle::move()
{
    if( disable )
        return;         // Если шар полностью не активен выходим из функции

    if( !active )
    {
        if( radius <= 50 && timer > 0 )
            radius += 2;

        if( radius >= 50 && timer > 0 ) timer -= 1;
        else if( timer == 0 )
        {
            if(radius > 0)
                radius -= 5;
            else { disable = true;  return; }
        }

        return;
    }

    // Изменяем положение центра круга на координатной плоскости
    x += vx;
    y += vy;

    if(moveMode) {
        // Если координата выходит за границы задаем ей противоположное значение
        if(x < radius) vx = fabs(vx);
        if(y < radius) vy = fabs(vy);

        if(x > width - radius) vx = -fabs(vx);
        if(y > height - radius) vy = -fabs(vy);
    }
    else {
        if( x < 0 ) x = width;
        if( y < 0 ) y = height;

        if( x > width ) x = 0;
        if( y > height ) y = 0;
    }
}

void Circle::deactivate()
{
    active = false;
    vx = 0;
    vy = 0;
    color[3] = 150;
}
