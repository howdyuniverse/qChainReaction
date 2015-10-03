#include <cmath>

#include "core/Circles.h"


Circles::Circles():totalHits(0)
{
    init(0);
}

Circles::~Circles()
{
    delete head;
}

void Circles::init(int s_total)
{
    totalHits = s_total;
    hits = 0;

    head = new Node;
    tail = head;

    tail->next = new Node;
    tail = tail->next;
    cursor = tail;

    cursor->circle.setCursorParameters();

    tail->next = 0;
}

void Circles::add(bool c_mode)
{
    tail->next = new Node;
    tail = tail->next;
    tail->next = 0;

    tail->circle.setMoveMode(c_mode);
    tail->circle.genDirection();
}

void Circles::clean()
{
    Node *current = head;
    Node *next = head->next;

    while( next )
    {
        current = next;
        next = next->next;
        delete current;
    }
}

void Circles::drawAllCircles(Drawing &dd)
{
    for (Node *t = head->next; t; t = t->next)
        t->circle.draw(dd);
}

// Двигаем все объекты
void Circles::moveCircles()
{
    for (Node *t = head->next; t; t = t->next)
        t->circle.move();
}

// Проверяем пересечения
void Circles::checkIntersection()
{
    // Условие выполняется только один раз - при нажатии
    // Начинаем цепную рекцию с курсора - он у нас первый элемент в списке
    if( cursor->circle.getActive() )
        cursor->circle.deactivate();

    for (Node *aCircle = head->next; aCircle; aCircle = aCircle->next)

        // Если круг не жив и еще активен
        if( !aCircle->circle.getActive() && !aCircle->circle.getDisable() )
            // проверяем пересечение с остальными
            for (Node *bCircle = head->next; bCircle; bCircle = bCircle->next)

                // Если проверяемый круг еще жив проверяем пересечение
                if( bCircle->circle.getActive() ) {
                    float a_x = aCircle->circle.getX();
                    float a_y = aCircle->circle.getY();
                    float a_r =  aCircle->circle.getR();

                    float b_x = bCircle->circle.getX();
                    float b_y = bCircle->circle.getY();
                    float b_r = bCircle->circle.getR();

                    //Формула проверки пересечения двух окуржностей
                    // V(x1 - x2)^2 + (y1 - y2)^2 <=  r1 + r2
                    float dist = sqrt( pow(( b_x - a_x ), 2) + pow(( b_y - a_y ), 2) );

                    if (dist <= a_r + b_r )
                    {
                        // Добавляем очки за попадание
                        hits++;
                        // Если попадает останавливаем круг
                        bCircle->circle.deactivate();
                    }
                }
}

bool Circles::checkEndLevel()
{
    for(Node *aCircle = head->next; aCircle; aCircle = aCircle->next)

        // Если находим хоть одно промежуточное состояние возвращаем false
        if( !aCircle->circle.getActive() && !aCircle->circle.getDisable() )
            return false;

    // Если цикл не нашел промежуточных состояний, ф-я возвращает сигнал об окночании уровня
    return true;
}

void Circles::setCursorCoords(float s_cx, float s_cy)
{
    cursor->circle.setCursorCoords(s_cx, s_cy);
}

int Circles::getHits()
{
    return hits;
}
