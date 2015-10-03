#ifndef CIRCLE_H
#define CIRCLE_H

#include "core/Drawing.h"

class Circle {
    float x;    // Положение центра круга в окне
    float y;
    float vx; // Скорость движения круга по осям
    float vy;
    bool moveMode;  // Режим движения Строгое или Хаос
    float radius; // Радиус круга

    bool active;    // показывает активность шарика
    bool disable;  // показывает полную деактивацию шарика
    int timer;

    unsigned char color[4]; // цвет

public:
    Circle();

    void genDirection();

    void setCursorParameters();
    void setCursorCoords(float s_x, float s_y) { x = s_x; y = s_y; }
    void setMoveMode(bool s_mmode) { moveMode = s_mmode; }

    void draw(Drawing &param_d);
    void move();
    void deactivate();

    float getX() const { return x; }
    float getY() const { return y; }
    float getR() const { return radius; }

    bool getActive()    const { return active;  }
    bool getDisable() const { return disable; }
};

#endif
