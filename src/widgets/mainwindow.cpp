#include <QtGui>
#include <QtOpenGL>

#include "widgets/mainwindow.h"
#include "widgets/glwidget.h"
#include "widgets/recordsdialog.h"


MainWindow::MainWindow()
{
    glWidget = new GLWidget;   // Создаем виджет OpenGL
    setCentralWidget(glWidget);   // И делаем его центральным

    setWindowTitle( tr("Гра ланцюгова реакція v0.7.6.11q") );
    setFixedSize(700, 450);

    createMenus();
    createActions();

    recordsDialog = 0;

    setWindowIcon(QIcon(":/icon.png"));
}

void MainWindow::createMenus()
{
    gameMenu = menuBar()->addMenu( tr("Гра") );
    helpMenu = menuBar()->addMenu( tr("Довідка") );
}

void MainWindow::createActions()
{
    newGameChaosAct     = gameMenu->addAction( tr("Нова гра (Хаос)") );
    newGameStraightAct  = gameMenu->addAction( tr("Нова гра (По прямій)") );
    resetLevelAction        = gameMenu->addAction( tr("Скинути поточний рівень") );
    recordsAction           = gameMenu->addAction( tr("Рекорди") );

    gameMenu->addSeparator();   // Линия в меню

    quitAction                  = gameMenu->addAction( tr("Вихід") );
    helpAction                  = helpMenu->addAction( tr("Як грати?") );

    helpMenu->addSeparator();

    aboutAction                 = helpMenu->addAction( tr("Про гру") );

    // hot keys
    newGameChaosAct->setShortcut        ( QKeySequence(Qt::CTRL | Qt::Key_C) );
    newGameStraightAct->setShortcut ( QKeySequence(Qt::CTRL | Qt::Key_S) );
    resetLevelAction->setShortcut       ( QKeySequence(Qt::Key_Space) );
    quitAction->setShortcut             ( QKeySequence(Qt::CTRL | Qt::Key_Q) );
    helpAction->setShortcut             ( QKeySequence(Qt::Key_F1) );

    // Connect
    connect( newGameChaosAct, SIGNAL(triggered()),
                     this, SLOT( newGameChaos()));
    connect( newGameStraightAct, SIGNAL(triggered()),
                     this, SLOT( newGameStraight()));
    connect( resetLevelAction, SIGNAL(triggered()),
                     this, SLOT( resetGame()));
    connect( recordsAction, SIGNAL(triggered()),
                     this, SLOT( records()));
    connect( quitAction, SIGNAL(triggered()),
                     this, SLOT( close()));
    connect( helpAction, SIGNAL(triggered()),
                     this, SLOT( manualGame()));
    connect( aboutAction, SIGNAL(triggered()),
                     this, SLOT( about()));
}

void MainWindow::resetGame()
{
    glWidget->resetGame();
}

void MainWindow::newGameChaos()
{
    glWidget->newGameChaos();
}

void MainWindow::newGameStraight()
{
    glWidget->newGameStraight();
}

void MainWindow::records()
{
    recordsDialog = new RecordsDialog( glWidget->getRec() );

    recordsDialog->show();
    recordsDialog->raise();
    recordsDialog->activateWindow();
}


void MainWindow::manualGame()
{
    QMessageBox::information(this, tr("Допомога"),
                                                    tr(
    "<h1>Як грати?</h1>"
    "<p align='justify'>У грі всього 8 рівнів, с кожним рівнем кількість кульок  <br>"
    "збільшується на 5. У вас під контролем є всього одна кулька "
    "за допомогою якої вам потрібно викликати ланцюгову реакцію, "
    "зачепивши тим самим як можна більше неконтрольованих кульок. "
    "Для того щоб перейти на наступний рівень вам потрібно "
    "подолати певний бар’єр встановлений поточним рівнем.</p>"
    "<p>Пробіл — Cкинути поточний рівень</p>"
    "<p>ctrl+c — Почати нову гру у режимі Хаос</p>"
    "<p>ctrl+s — Почати нову гру у режимі По прямій</p>"
    "<p>ctrl+q — Вийти з гри</p>"
                                                         )
                                                    );
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("Про гру Ланцюгова реакція v0.7.6.11q"),
        tr("<b>Ланцюгова реакція — v0.7.6.11 Qt version</b>"
            "<br>Невелика гра створена за допомогою OpenGL та Qt4."
            ));
}
