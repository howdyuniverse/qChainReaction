#include "glwidget.h"
#include <QtOpenGL>
#include <QtGui>

#include <QTextCodec>

GLWidget::GLWidget(QWidget *parent) :  QGLWidget(parent)
{
    setMouseTracking(true); // включаем отслеживание мыши
   setFixedSize(700, 430);

     QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT( advanceGame() ));
     timer->start(20);
}

GLWidget::~GLWidget()
{
    makeCurrent();
}

void GLWidget::initializeGL() //вызывается только один раз перед вызовом функции paintGL().
{
    glClearColor(0.0, 0.27, 0.27, 1.0);
//  glClearColor(0.15, 0.38, 0.50, 1.0); // - blue
//  glClearColor(0.39, 0.43, 0.40, 1.0); //- good
    //glClearColor(0.0, 0.3, 0.3, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 700, 430, 0, -1, 1);
    glViewport( 0, 0, 700, 430 );

    CRgame.initDraw();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    CRgame.drawGame();

    drawTextInfo();
}

void GLWidget::advanceGame()
{
    CRgame.update();
    updateGL();
}

void GLWidget::drawTextInfo()
{
    QString t = "Рівень: " + QString::number( CRgame.retLevel() );
    t = t + "  |  Влучень: " + QString::number( CRgame.retScore() ) + "/"
         + QString::number( CRgame.retNLScore() );
    t = t + "  |  Всього: " + QString::number( CRgame.retTotal() );

    glColor3ub(255, 255, 255);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    renderText( 10, 17, t, QFont("Verdana", 10) );

    if( CRgame.retGameStatus() == 1 ) {
        glColor3ub(255, 255, 255);
        renderText( 175, 190, "Ви подолали рівень!", QFont("Comic Sans MS", 15) );
        renderText( 175, 220, "Натисніть ПРОБІЛ щоб продовжити...", QFont("Comic Sans MS", 15) );
    }
    else if( CRgame.retGameStatus() == 2 ) {
        glColor3ub(255, 255, 255);
        renderText( 290, 205, "Спробуй ще...", QFont("Comic Sans MS", 15) );
    }
    else if( CRgame.retGameStatus() == 3 ) {
        glColor3ub(255, 255, 255);
        renderText( 210, 200, "Ви виграли! Ваш результат: "
                        + QString::number( CRgame.retTotal() ), QFont("Comic Sans MS", 15) );
        if( CRgame.retRecordIndex() != -1 ) {
            glColor3ub(18, 138, 229);
            renderText( 157, 230, "Ви також встановили новий рекорд у грі!", QFont("Comic Sans MS", 15) );
        }
    }
}

void GLWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
   if( mouseEvent->buttons() & Qt::LeftButton )
      CRgame.buttonIsPressed();
}

void GLWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
   QPoint lastPos;
   lastPos = mouseEvent->pos();
   CRgame.setCurCoords( GLfloat( lastPos.x() ), GLfloat( lastPos.y() ) );
}
