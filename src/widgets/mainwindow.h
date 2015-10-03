#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GLWidget;
class RecordsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void about();
    void manualGame();

    void resetGame();
    void newGameChaos();
    void newGameStraight();
    void records();

private:
    GLWidget *glWidget;          // Виджет OpenGL
    RecordsDialog   *recordsDialog; // Окно рекордов

    // Menu
    QMenu *gameMenu;
    QMenu *helpMenu;

    QAction *newGameChaosAct;
    QAction *newGameStraightAct;

    QAction *resetLevelAction;

    QAction *recordsAction;
    QAction *quitAction;

    QAction *helpAction;
    QAction *aboutAction;

    void createActions();
    void createMenus();
};

#endif // MAINWINDOW_H
