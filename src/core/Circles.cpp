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
    if( cursor->circle.getActive() )        // Условие выполняется только один раз - при нажатии
        cursor->circle.deactivate();    // Начинаем цепную рекцию с курсора - он у нас первый элемент в списке
    
    for (Node *a = head->next; a; a = a->next)

        if( !a->circle.getActive() && !a->circle.getDisable() ) // Если круг не жив и еще активен
            for (Node *b = head->next; b; b = b->next)          // проверяем пересечение с остальными

                // Если проверяемый круг еще жив проверяем пересечение
                if( b->circle.getActive() )

                    //Формула проверки пересечения двух окуржностей
                    // V(x1 - x2)^2 + (y1 - y2)^2 <=  r1 + r2
                    if (sqrt( pow(( b->circle.getX() - a->circle.getX() ), 2) + pow(( b->circle.getY() - a->circle.getY() ), 2) ) <= a->circle.getR() + b->circle.getR() )
                    {
                        hits++;     // Добавляем очки за попадание
                        b->circle.deactivate(); // Если попадает останавливаем круг
                    }
}

bool Circles::checkEndLevel()
{
    for(Node *a = head->next; a; a = a->next)

        // Если находим хоть одно промежуточное состояние возвращаем false
        if( !a->circle.getActive() && !a->circle.getDisable() )
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
