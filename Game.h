#ifndef GAME_H
#define GAME_H

#include "Circle.h"
#include "Circles.h"
class Drawing;

class Game {
    enum { LEVELS = 8, RECORDS = 10 };

    Circles circles;
    Drawing draw;

    int level;  // уровень
    int score;  // количество очков
    int total;
    int nextLevelScore[LEVELS]; //
    int records[RECORDS];
    int recordIndex;

    int status;

    // Курсор
    bool click;

    bool mode;
    bool spaceButton;
    bool gotoNextLevel;
    bool endGame;

    void loadRecordsFile();
    void writeRecordsFile();
    void checkNewRecord();

public:
    Game();

    void reset();
    void drawGame();    // Рисуем все элементы игры
    void update();      // Обновляем положение элементов в окне

    void setCurCoords(float xx, float yy);
    void spaceEvent();
    void initDraw();

    void newGame(bool s_mode);  // Новая игра сначала

    void buttonIsPressed() {click = true;}

    // for qt
    int retScore()   { return score; }
    int retNLScore() { return nextLevelScore[level-1]; }
    int retLevel()   { return level; }
    int retTotal()   { return total; }

    int *retRecords()       { return records; }
    int retGameStatus() { return status; }
    int retRecordIndex() { return recordIndex; }
};

#endif
