#ifndef CIRCLES_H
#define CIRCLES_H

#include "Circle.h"
class Drawing;

struct Node
{
    Circle circle;
    Node *next;
};

class Circles
{
    Node *head;
    Node *tail;
    Node *cursor;
    int hits;
    int totalHits;

public:
    Circles();
    ~Circles();

    void init(int s_total); //_

    void add(bool c_mode); // Добавление одного курга в список
    void clean(); // Очистка списка
    void drawAllCircles(Drawing &dd); // Рисование всех кругов в списке
    void moveCircles(); // Двигаем все объекты

    void checkIntersection();       // Проверяем пересечения
    bool checkEndLevel();           // Проверка на окончание игры

    void setCursorCoords(float s_cx, float s_cy);
    int  getHits();
};

#endif
