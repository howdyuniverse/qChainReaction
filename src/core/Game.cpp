#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "core/Game.h"

using namespace std;


Game::Game():level(1), score(0), total(0), recordIndex(-1), status(0), mode(1)
{
    srand( unsigned(time(NULL)) );

    for(int i = 0; i < RECORDS; ++i)
        records[i] = 0; // init recrods

    loadRecordsFile();
    
    for(int n = 0; n < LEVELS; ++n)
        nextLevelScore[n] = (n*n + n + 2) / 2;  // Lazy caterer's sequence

    reset();
}

void Game::reset()
{
    circles.clean();
    circles.init(total);


    click               = false;
    spaceButton     = false;
    gotoNextLevel   = false;

    score = 0;
    status = 0;
    recordIndex = -1;

    for(int i = 0; i < level*5; ++i)
        circles.add(mode);
}

void Game::newGame(bool s_mode) // Создает новую игру с первого уровня
{
    mode = s_mode;
    level = 1;
    total = 0;
    recordIndex = 0;
    reset();
}

void Game::drawGame()
{
    circles.drawAllCircles(draw);
    draw.drawInfoPanel();

    if( score >= nextLevelScore[level-1] && gotoNextLevel && level < LEVELS ) {
        draw.drawWindowWin();
        status = 1;
    }
    else if( score < nextLevelScore[level-1] && gotoNextLevel ) {
        draw.drawWidnowRepeat();
        status = 2;
    }
    else if( level == LEVELS && gotoNextLevel ) {
        draw.drawFinalBackground();
        status = 3;
    }
}

void Game::update()
{
    if( click && !gotoNextLevel )   // Когда была нажата клавиша мыши
    {
        circles.checkIntersection();                // Вызываем ф-ю проверки перечесечения
        gotoNextLevel = circles.checkEndLevel();    // Проверка на окончание уровня
        score = circles.getHits();                  // Количество попаданий

        if(level == LEVELS) // Если текущий уровень последний
            if( gotoNextLevel && score >= nextLevelScore[level-1] )
            {
                total += score;
                checkNewRecord();   // Проверка на новый рекорд
                if( recordIndex != -1 ) // Если рекорд установлен
                    writeRecordsFile(); // Перезаписываем файл
            }
    }

    circles.moveCircles();
}

void Game::setCurCoords(float xx, float yy)
{
    if( !click )
        circles.setCursorCoords(xx, yy);
}

void Game::spaceEvent()
{
    if( score < nextLevelScore[level-1] )
        reset();
    else if( score >= nextLevelScore[level-1] && level < LEVELS )
    {
        ++level;
        total += score;
        reset();
    }
    if( score >= nextLevelScore[level-1] && level == LEVELS )
    {
        endGame = false;
        level = 1;
        total = 0;
        reset();
    }
}

void Game::initDraw()
{
    draw.initDisplayList();
}

void Game::writeRecordsFile()
{
    ofstream o("records");
    for(int i = 0; i < RECORDS; ++i)
        o << records[i] << "\n";
    o.close();
}

void Game::loadRecordsFile()
{
    ifstream iout("records");
    for(int i = 0; i < RECORDS; ++i)
        iout >> records[i];
    iout.close();
}

void Game::checkNewRecord()
{
    int rec = mode?RECORDS-5:RECORDS;
    for(int i = rec-5; i < rec; ++i)
        if( total > records[i] )    // Если число набранных очков будет больше чем остальные рекорды
        {
            for(int j = rec-1; j > i; --j)  // Обновляем таблицу рекордов
            {
                records[j] = records[j-1];
            }
            records[i] = total;
            recordIndex = i;

            return;
        }
    recordIndex = -1;
}
