#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include "Game.h"


class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
	GLWidget( QWidget *parent = 0 );
	~GLWidget();

    void resetGame()
    { CRgame.spaceEvent(); }

    void newGameChaos()
    { CRgame.newGame(1); }

    void newGameStraight()
    { CRgame.newGame(0); }

    int *getRec()
    { return CRgame.retRecords(); }

protected:
	void initializeGL();
	void paintGL();

    void mousePressEvent
    ( QMouseEvent *mouseEvent );

    void mouseMoveEvent
    ( QMouseEvent *mouseEvent );


private:
   Game CRgame;

	void drawTextInfo();

private slots:
	void advanceGame();

};

#endif // GLWIDGET_H
